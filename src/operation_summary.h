#ifndef ADVANCED_TOOLS_OPERATION_SUMMARY_H
#define ADVANCED_TOOLS_OPERATION_SUMMARY_H

struct OperationSummary{
    char const* label;
    double average_time;
    double min_time;
    double max_time;
    double mb_per_second;
};
#endif //ADVANCED_TOOLS_OPERATION_SUMMARY_H
