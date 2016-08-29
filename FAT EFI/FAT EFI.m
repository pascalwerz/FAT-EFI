//
//  FAT EFI.m
//  FAT EFI
//
//  Created by Pascal on 16/08/2016.
//  Copyright © 2016 xvi. All rights reserved.
//

#import "FAT EFI.h"
#import "cpu_names.h"


@implementation FATEFI


id<HPHopperServices> _services;




- (instancetype)initWithHopperServices:(NSObject<HPHopperServices> *)services
{
    if (self = [super init])
    {
        _services = services;
    }

    return self;
}



- (HopperUUID *)pluginUUID
{
    return [_services UUIDWithString:@"F25232B2-1220-4E78-A49B-927E4F592523"];
}



- (HopperPluginType)pluginType
{
    return Plugin_Loader;
}



- (NSString *)pluginName
{
    return @"FAT EFI";
}



- (NSString *)pluginDescription
{
    return @"FAT EFI binary loader";
}



- (NSString *)pluginAuthor
{
    return @"Pascal Werz";
}



- (NSString *)pluginCopyright
{
    return @"© Pascal Werz, released under GPL.";
}



- (NSString *)pluginVersion
{
    return @"0.1.1";
}



- (BOOL)canLoadDebugFiles
{
    // this is a composite loader
    return NO;
}



- (NSArray *)detectedTypesForData:(NSData *)data
{
    id<HPDetectedFileType> detectedType = [_services detectedType];
    BOOL needToSwap = NO;
    struct fatefi_header header;
    struct fatefi_arch arch;
    NSMutableArray * list = [NSMutableArray array];
    const uint8_t * dataBytes = [data bytes];
    NSUInteger dataLength = [data length];

    // get the FAT EFI header
    memcpy(&header, dataBytes, sizeof(struct fatefi_header));

    if (header.magic == FATEFI_CIGAM) needToSwap = YES;

    if (needToSwap)
    {
        header.magic = CFSwapInt32(header.magic);
        header.nfat_arch = CFSwapInt32(header.nfat_arch);
    }

    // parse thru all FAT EFI architectures
    if (header.magic != FATEFI_MAGIC) return nil;
    {
        for (int i = 0; i < header.nfat_arch; i++)
        {
            memcpy(&arch, dataBytes + sizeof(struct fatefi_header) + i * sizeof(struct fatefi_arch), sizeof(struct fatefi_arch));
            if (needToSwap)
            {
                arch.cputype = CFSwapInt32(arch.cputype);
                arch.cpusubtype = CFSwapInt32(arch.cpusubtype);
                arch.offset = CFSwapInt32(arch.offset);
                arch.size = CFSwapInt32(arch.size);
                arch.align = CFSwapInt32(arch.align);
            }

            // sanity check: ensure PE is completely enclosed in the file
            if (arch.offset < dataLength && (arch.offset + arch.size) <= dataLength)
            {
                // this is a composite loader
                detectedType.compositeFile = YES;
                detectedType.fileDescription = @"FAT EFI binary";
                detectedType.shortDescriptionString = @"FAT EFI";

                // build list that will be displayed as a choice for user
                [list addObject:[NSString stringWithUTF8String:find_cpu_name(arch.cputype, arch.cpusubtype)]];

            }
        }
        // add the choice list to the returned detected type
        detectedType.additionalParameters = @[[_services stringListComponentWithLabel:@"CPU" andList:list]];
    }

    return @[detectedType];

}



- (FileLoaderLoadingStatus)loadData:(NSData *)data usingDetectedFileType:(DetectedFileType *)fileType options:(FileLoaderOptions)options forFile:(NSObject<HPDisassembledFile> *)file usingCallback:(FileLoadingCallbackInfo)callback
{
    // this is a composite loader
    return DIS_NotSupported;
}



- (FileLoaderLoadingStatus)loadDebugData:(NSData *)data forFile:(NSObject<HPDisassembledFile> *)file usingCallback:(FileLoadingCallbackInfo)callback
{
    // this is a composite loader
    return DIS_NotSupported;
}



/// Extract a file
/// In the case of a "composite loader", extract the NSData object of the selected file.
- (NSData *)extractFromData:(NSData *)data
      usingDetectedFileType:(NSObject<HPDetectedFileType> *)fileType
         returnAdjustOffset:(uint64_t *)adjustOffset
{
    struct fatefi_header header;
    struct fatefi_arch arch;
    BOOL needToSwap = NO;
    NSUInteger index = ((id <HPLoaderOptionComponents>)[(NSArray *)fileType.additionalParameters objectAtIndex:0]).selectedStringIndex;
    const uint8_t * dataBytes = [data bytes];
    NSUInteger dataLength = [data length];
    NSData * result = nil;

    // get the header
    memcpy(&header, dataBytes, sizeof(struct fatefi_header));
    if (header.magic == FATEFI_CIGAM) needToSwap = YES;

    if (needToSwap)
    {
        header.magic = CFSwapInt32(header.magic);
        header.nfat_arch = CFSwapInt32(header.nfat_arch);
    }

    if (header.magic != FATEFI_MAGIC) return nil;

    // get the chosen PE
    memcpy(&arch, dataBytes + sizeof(struct fatefi_header) + index * sizeof(struct fatefi_arch), sizeof(struct fatefi_arch));
    if (needToSwap)
    {
        arch.cputype = CFSwapInt32(arch.cputype);
        arch.cpusubtype = CFSwapInt32(arch.cpusubtype);
        arch.offset = CFSwapInt32(arch.offset);
        arch.size = CFSwapInt32(arch.size);
        arch.align = CFSwapInt32(arch.align);
    }

    // sanity check: ensure PE is completely enclosed in the file
    if (arch.offset < dataLength && (arch.offset + arch.size) <= dataLength)
    {
        result = [data subdataWithRange:NSMakeRange(arch.offset, arch.size)];
        *adjustOffset = 0; // ?
    }

    return result;
}



- (void)fixupRebasedFile:(id<HPDisassembledFile>)file
               withSlide:(int64_t)slide
        originalFileData:(NSData *)fileData
{
}


@end
