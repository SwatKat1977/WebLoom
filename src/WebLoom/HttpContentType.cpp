//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <stdexcept>
#include <unordered_map>
#include "HttpContentType.h"

namespace webloom::core {

const std::unordered_map<std::string, HttpContentType> contentTypeMap = {
    {"text/plain", HttpContentType::TextPlain},
    {"text/html", HttpContentType::TextHTML},
    {"text/css", HttpContentType::TextCSS},
    {"text/javascript", HttpContentType::TextJavaScript},
    {"text/xml", HttpContentType::TextXML},
    {"text/csv", HttpContentType::TextCSV},

    {"application/json", HttpContentType::ApplicationJSON},
    {"application/xml", HttpContentType::ApplicationXML},
    {"application/XHTML+XML", HttpContentType::ApplicationXHTMLXML},
    {"application/javascript", HttpContentType::ApplicationJavaScript},
    {"application/Octet-Stream", HttpContentType::ApplicationOctetStream},
    {"application/Form-Urlencoded", HttpContentType::ApplicationFormUrlencoded},
    {"application/pdf", HttpContentType::ApplicationPDF},
    {"application/zip", HttpContentType::ApplicationZip},
    {"application/gzip", HttpContentType::ApplicationGZip},
    {"application/sql", HttpContentType::ApplicationSQL},
    {"application/rtf", HttpContentType::ApplicationRTF},
    {"application/VND.MS-PowerPoint",
     HttpContentType::ApplicationVNDMSPowerPoint},
    {"application/vnd.ms-excel",
     HttpContentType::ApplicationVNDMSExcel},
    {"application/vnd.ms-Word",
     HttpContentType::ApplicationVNDMSWord},

    {"image/jpeg", HttpContentType::ImageJPEG},
    {"image/png", HttpContentType::ImagePNG},
    {"image/gif", HttpContentType::ImageGIF},
    {"image/bmp", HttpContentType::ImageBMP},
    {"image/webp", HttpContentType::ImageWebP},
    {"image/SVG+XML", HttpContentType::ImageSVGXML},
    {"image/tiff", HttpContentType::ImageTIFF},
    {"image/heic", HttpContentType::ImageHeic},
    {"image/x-icon", HttpContentType::ImageXIcon},

    {"audio/mpeg", HttpContentType::AudioMPEG},
    {"audio/ogg", HttpContentType::AudioOGG},
    {"audio/wav", HttpContentType::AudioWAV},

    {"video/mp4", HttpContentType::VideoMP4},
    {"video/mpeg", HttpContentType::VideoMPEG},
    {"video/ogg", HttpContentType::VideoOGG},
    {"video/webm", HttpContentType::VideoWebM},

    {"multipart/Form-Data",
     HttpContentType::MultipartFormData},
    {"multipart/Byteranges",
     HttpContentType::MultipartByteranges},

    {"font/TTF", HttpContentType::FontTTF},
    {"font/WOFF", HttpContentType::FontWOFF},
    {"font/WOFF2", HttpContentType::FontWOFF2},
    {"font/OTF", HttpContentType::FontOTF},
    {"application/VND.OASIS.OpenDocument.Text",
     HttpContentType::ApplicationVNDOASISOpenDocumentText},
    {"application/VND.OASIS.OpenDocument.Spreadsheet",
     HttpContentType::ApplicationVNDOASISOpenDocumentSpreadsheet}
};

std::string HttpContentTypeString(HttpContentType type) {
    switch (type) {
    case HttpContentType::TextPlain:
        return "text/plain";
    case HttpContentType::TextHTML:
        return "text/html";
    case HttpContentType::TextCSS: return "text/css";
    case HttpContentType::TextJavaScript: return "text/javascript";
    case HttpContentType::TextXML: return "text/xml";
    case HttpContentType::TextCSV: return "text/csv";

    case HttpContentType::ApplicationJSON: return "application/json";
    case HttpContentType::ApplicationXML: return "application/xml";
    case HttpContentType::ApplicationXHTMLXML: return "application/xhtml+xml";
    case HttpContentType::ApplicationJavaScript:
        return "application/javascript";
    case HttpContentType::ApplicationOctetStream:
        return "application/octet-stream";
    case HttpContentType::ApplicationFormUrlencoded:
        return "application/x-www-form-urlencoded";
    case HttpContentType::ApplicationPDF:
        return "application/pdf";
    case HttpContentType::ApplicationZip:
        return "application/zip";
    case HttpContentType::ApplicationGZip:
        return "application/gzip";
    case HttpContentType::ApplicationSQL:
        return "application/sql";
    case HttpContentType::ApplicationRTF:
        return "application/rtf";
    case HttpContentType::ApplicationVNDMSPowerPoint:
        return "application/vnd.ms-powerpoint";
    case HttpContentType::ApplicationVNDMSExcel:
        return "application/vnd.ms-excel";
    case HttpContentType::ApplicationVNDMSWord:
        return "application/msword";

    case HttpContentType::ImageJPEG:
        return "image/jpeg";
    case HttpContentType::ImagePNG:
        return "image/png";
    case HttpContentType::ImageGIF:
        return "image/gif";
    case HttpContentType::ImageBMP:
        return "image/bmp";
    case HttpContentType::ImageWebP:
        return "image/webp";
    case HttpContentType::ImageSVGXML:
        return "image/svg+xml";
    case HttpContentType::ImageTIFF:
        return "image/tiff";
    case HttpContentType::ImageHeic:
        return "image/heic";
    case HttpContentType::ImageXIcon:
        return "image/x-icon";

    case HttpContentType::AudioMPEG: return "audio/mpeg";
    case HttpContentType::AudioOGG: return "audio/ogg";
    case HttpContentType::AudioWAV: return "audio/wav";

    case HttpContentType::VideoMP4: return "video/mp4";
    case HttpContentType::VideoMPEG: return "video/mpeg";
    case HttpContentType::VideoOGG: return "video/ogg";
    case HttpContentType::VideoWebM: return "video/webm";

    case HttpContentType::MultipartFormData:
        return "multipart/form-data";
    case HttpContentType::MultipartByteranges:
        return "multipart/byteranges";

    case HttpContentType::FontTTF: return "font/ttf";
    case HttpContentType::FontWOFF: return "font/woff";
    case HttpContentType::FontWOFF2: return "font/woff2";
    case HttpContentType::FontOTF: return "font/otf";
    case HttpContentType::ApplicationVNDOASISOpenDocumentText:
        return "application/vnd.oasis.opendocument.text";
    case HttpContentType::ApplicationVNDOASISOpenDocumentSpreadsheet:
        return "application/vnd.oasis.opendocument.spreadsheet";

    default: return "unknown";
    }
}

HttpContentType HttpContentTypeStringToEnum(const std::string& typeStr) {
    auto it = contentTypeMap.find(typeStr);
    if (it != contentTypeMap.end()) {
        return it->second;
    }

    throw std::invalid_argument("Unknown content type: " + typeStr);
}

}   // namespace webloom::core
