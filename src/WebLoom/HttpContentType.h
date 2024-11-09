//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef HTTPCONTENTTYPE_H_
#define HTTPCONTENTTYPE_H_
#include <string>

namespace webloom {

enum class HttpContentType {
    // Text types
    TextPlain,
    TextHTML,
    TextCSS,
    TextJavaScript,
    TextXML,
    TextCSV,

    // Application types
    ApplicationJSON,
    ApplicationXML,
    ApplicationXHTMLXML,
    ApplicationJavaScript,
    ApplicationOctetStream,
    ApplicationFormUrlencoded,
    ApplicationPDF,
    ApplicationZip,
    ApplicationGZip,
    ApplicationSQL,
    ApplicationRTF,
    ApplicationVNDMSPowerPoint,
    ApplicationVNDMSExcel,
    ApplicationVNDMSWord,

    // Image types
    ImageJPEG,
    ImagePNG,
    ImageGIF,
    ImageBMP,
    ImageWebP,
    ImageSVGXML,
    ImageTIFF,
    ImageHeic,
    ImageXIcon,

    // Audio types
    AudioMPEG,
    AudioOGG,
    AudioWAV,

    // Video types
    VideoMP4,
    VideoMPEG,
    VideoOGG,
    VideoWebM,

    // Multipart types
    MultipartFormData,
    MultipartByteranges,

    // Other types
    FontTTF,
    FontWOFF,
    FontWOFF2,
    FontOTF,
    ApplicationVNDOASISOpenDocumentText,
    ApplicationVNDOASISOpenDocumentSpreadsheet
};

std::string HttpContentTypeString(HttpContentType type);

HttpContentType HttpContentTypeStringToEnum(const std::string& typeStr);

}   // namespace webloom

#endif  // HTTPCONTENTTYPE_H_
