#include "structures.hpp"
// -----------------------------------------------------------------------------
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <unordered_set>
#include <unordered_map>
// You are free to add any STL includes above this comment, below the --line--.
// DO NOT add "using namespace std;" or include any other files/libraries.
// Also DO NOT add the include "bits/stdc++.h"

// OPTIONAL: Add your helper functions and classes here

class plagiarism_checker_t {
    // You should NOT modify the public interface of this class.
public:
    plagiarism_checker_t(void);
    plagiarism_checker_t(std::vector<std::shared_ptr<submission_t>> 
                            __submissions);
    ~plagiarism_checker_t(void);
    void add_submission(std::shared_ptr<submission_t> __submission);

protected:
    // TODO: Add members and function signatures here

    // Structure to hold data related to a single submission.
    // Includes the submission pointer, its tokenized representation, and timestamp of submission.
    struct SubmissionData {
        std::shared_ptr<submission_t> submission; // Pointer to the submission object.
        std::vector<int> tokens; // Tokenized representation of the submission's code.
        // Time when the submission was received or processed.
        std::chrono::time_point<std::chrono::steady_clock> timestamp; 
    };

    // Continuously processes submissions from the queue.
    void worker(); 
    // Checks a submission for plagiarism.
    void check_plagiarism(const SubmissionData& new_submission); 
    // Compares token sequences for plagiarism.
    bool is_plagiarized(const std::vector<int>& new_tokens, const std::vector<int>& old_tokens); 
    // Detects patchwork plagiarism.
    bool check_patchwork(const std::vector<int>& new_tokens, 
                            const std::vector<const SubmissionData*>& existing_submissions); 
    // Flags a submission as plagiarized.
    void flag_submission(std::shared_ptr<submission_t> submission); 

    std::vector<SubmissionData> base_submissions_; // Base submissions for comparison.
    std::vector<SubmissionData> submissions_; // Processed submissions for future checks.
    std::vector<SubmissionData> queue_; // Pending submissions waiting to be processed.
    std::mutex mutex_; // Ensures thread-safe access to shared resources.
    std::condition_variable cv_; // Notifies worker thread about new work.
    std::thread worker_thread_; // Background thread for processing submissions.
    bool stop_thread_; // Flag to signal the worker thread to stop.

    // End TODO
};
