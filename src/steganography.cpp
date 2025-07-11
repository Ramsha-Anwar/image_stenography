#include "steganography.h"
#include <opencv2/opencv.hpp>
#include <bitset>
#include <string>
#include <iostream>

void encodeMessage(cv::Mat& image, const std::string& message) {
    cv::Mat img = image.clone();
    int totalPixels = img.rows * img.cols;

    std::string binaryMsg;
    for (char c : message) {
        binaryMsg += std::bitset<8>(c).to_string();
    }
    binaryMsg += "00000000"; // Null terminator

    if (binaryMsg.size() > totalPixels * 3) {
        std::cerr << "Message too long to encode in this image." << std::endl;
        return;
    }

    int idx = 0;
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            for (int c = 0; c < 3; ++c) {
                if (idx < binaryMsg.size()) {
                    img.at<cv::Vec3b>(i, j)[c] &= 0xFE;
                    img.at<cv::Vec3b>(i, j)[c] |= (binaryMsg[idx] == '1');
                    idx++;
                }
            }
        }
    }

    image = img;
}

std::string decodeMessage(const cv::Mat& image) {
    cv::Mat img = image;
    if (img.empty()) {
        std::cerr << "Error reading image for decoding." << std::endl;
        return "";
    }

    std::string bits;
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            for (int c = 0; c < 3; ++c) {
                bits += (img.at<cv::Vec3b>(i, j)[c] & 1) ? '1' : '0';
            }
        }
    }

    std::string result;
    for (size_t i = 0; i + 8 <= bits.size(); i += 8) {
        std::bitset<8> byte(bits.substr(i, 8));
        char c = static_cast<char>(byte.to_ulong());
        if (c == '\0') break;
        result += c;
    }
    return result;
}
// Encode and decode logic using OpenCV

