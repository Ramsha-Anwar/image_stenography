#pragma once
#include <string>
#include <opencv2/core.hpp>

// Encodes a message into an image (in-place)
void encodeMessage(cv::Mat& image, const std::string& message);

// Decodes and returns a message from an image
std::string decodeMessage(const cv::Mat& image);
