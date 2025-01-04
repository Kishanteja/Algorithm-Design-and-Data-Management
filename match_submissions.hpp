#include <array>
#include <iostream>
#include <vector>
#include <span>
#include <cmath>
#include <unordered_map>

// Calculate the similarity score between two segments
double calculateSimilarity(const std::vector<int>& segment1,
                           const std::vector<int>& segment2,
                           size_t start1,
                           size_t start2,
                           size_t length) {
    int matchCount = 0;
    for (size_t i = 0; i < length; ++i) {
        if (segment1[start1 + i] == segment2[start2 + i]) {
            matchCount++;
        }
    }
    return static_cast<double>(matchCount) / length;
}

// Helper function for checking exact matches between segments
bool isExactMatch(const std::vector<int>& data1, const std::vector<int>& data2,
                  size_t start1, size_t start2, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (data1[start1 + i] != data2[start2 + i]) return false;
    }
    return true;
}

// Calculate hash for a segment using rolling hash technique
size_t computeSegmentHash(const std::vector<int>& data, size_t start, size_t length) {
    const size_t primeBase = 31;
    const size_t modulus = 1e9 + 9;
    size_t hashValue = 0;
    size_t primePower = 1;

    for (size_t i = 0; i < length; ++i) {
        hashValue = (hashValue + (data[start + i] * primePower) % modulus) % modulus;
        primePower = (primePower * primeBase) % modulus;
    }
    return hashValue;
}

// Sliding window optimization for searching long patterns
void searchForLongPatterns(const std::vector<int>& submission1,
                           const std::vector<int>& submission2,
                           size_t windowSize, int& maxMatchLength,
                           int& startIndex1, int& startIndex2) {
    const size_t stepSize = windowSize / 4;
    std::unordered_map<size_t, std::vector<size_t>> hashMap;
    for (size_t i = 0; i + windowSize <= submission2.size(); i += stepSize) {
        size_t hash = computeSegmentHash(submission2, i, windowSize);
        hashMap[hash].push_back(i);
    }
    for (size_t i = 0; i + windowSize <= submission1.size(); i += stepSize) {
        size_t hash = computeSegmentHash(submission1, i, windowSize);
        if (hashMap.count(hash)) {
            for (size_t pos : hashMap[hash]) {
                double similarityScore = calculateSimilarity(
                    submission1, submission2, i, pos, windowSize);
                if (similarityScore >= 0.8) {
                    if (windowSize > maxMatchLength) {
                        maxMatchLength = windowSize;
                        startIndex1 = i;
                        startIndex2 = pos;
                    }
                }
            }
        }
    }
}

// Exact match detection with rolling hash optimization
void detectExactMatches(const std::vector<int>& submission1,
                        const std::vector<int>& submission2,
                        std::vector<bool>& usedInSubmission1,
                        std::vector<bool>& usedInSubmission2,
                        int& totalExactMatchLength) {
    const size_t minLength = 10;
    const size_t maxLength = 20;
    for (size_t len = maxLength; len >= minLength; --len) {
        std::vector<size_t> hashesForSubmission2(submission2.size() - len + 1);
        for (size_t j = 0; j + len <= submission2.size(); ++j) {
            hashesForSubmission2[j] = computeSegmentHash(submission2, j, len);
        }
        for (size_t i = 0; i + len <= submission1.size(); ++i) {
            bool isUsed = false;
            for (size_t k = i; k < i + len; ++k) {
                if (usedInSubmission1[k]) {
                    isUsed = true;
                    break;
                }
            }
            if (isUsed) continue;
            size_t hash1 = computeSegmentHash(submission1, i, len);
            for (size_t j = 0; j + len <= submission2.size(); ++j) {
                if (usedInSubmission2[j] || hash1 != hashesForSubmission2[j]) continue;
                if (isExactMatch(submission1, submission2, i, j, len)) {
                    for (size_t k = 0; k < len; ++k) {
                        usedInSubmission1[i + k] = true;
                        usedInSubmission2[j + k] = true;
                    }
                    totalExactMatchLength += len;
                    break;
                }
            }
        }
    }
}

// Improved longest common subsequence detection
void findLongestCommonSubsequence(const std::vector<int>& submission1,
                                   const std::vector<int>& submission2, int& maxLCSLength,
                                   int& startIndex1, int& startIndex2) {
    const size_t m = submission1.size();
    const size_t n = submission2.size();
    const int minLength = 30;
    const double matchThreshold = 0.8;
    std::vector<int> previousRow(n + 1, 0), currentRow(n + 1, 0);
    maxLCSLength = 0; startIndex1 = 0; startIndex2 = 0;
    int currentPatternLength = 0;
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (submission1[i - 1] == submission2[j - 1]) {
                currentRow[j] = previousRow[j - 1] + 1;
                currentPatternLength = currentRow[j];
                int windowSize = std::max(currentPatternLength, minLength);
                if (currentPatternLength >= minLength && 
                    currentPatternLength >= windowSize * matchThreshold) {
                    if (currentPatternLength > maxLCSLength) {
                        maxLCSLength = currentPatternLength;
                        startIndex1 = i - maxLCSLength;
                        startIndex2 = j - maxLCSLength;
                    }
                }
            } else {
                currentRow[j] = 0;
            }
        }
        std::swap(previousRow, currentRow);
    }
    if (maxLCSLength < minLength) {
        searchForLongPatterns(submission1, submission2, minLength, 
                              maxLCSLength, startIndex1, startIndex2);
    }
    if (maxLCSLength < minLength) {
        maxLCSLength = startIndex1 = startIndex2 = 0;
    }
}

std::array<int, 5> match_submissions(std::vector<int>& submission1,
                                     std::vector<int>& submission2) {
    std::array<int, 5> result = {0, 0, 0, 0, 0};
    std::vector<bool> usedInSubmission1(submission1.size(), false);
    std::vector<bool> usedInSubmission2(submission2.size(), false);

    int totalExactMatchLength = 0;
    detectExactMatches(submission1, submission2, usedInSubmission1, usedInSubmission2, 
                                                                totalExactMatchLength);

    int longestCommonSubsequenceLength = 0, startIndex1 = 0, startIndex2 = 0;
    findLongestCommonSubsequence(submission1, submission2, longestCommonSubsequenceLength, 
                                                                startIndex1, startIndex2);
    
    const double exactMatch = 0.2;
    const double approximateMatch = 0.3;
    int minSubmissionSize = std::min(submission1.size(), submission2.size());
    bool hasSignificantExactMatches = 
        totalExactMatchLength >= static_cast<int>(minSubmissionSize * exactMatch);
    bool hasSignificantLongMatch = 
        longestCommonSubsequenceLength >= static_cast<int>(minSubmissionSize * approximateMatch);
    result[0] = (hasSignificantExactMatches || hasSignificantLongMatch) ? 1 : 0;
    result[1] = totalExactMatchLength;
    result[2] = longestCommonSubsequenceLength;
    result[3] = startIndex1;
    result[4] = startIndex2;
    return result;
}
