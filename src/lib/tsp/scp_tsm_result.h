#ifndef SCP_A2_TSM_RESULT_H_
#define SCP_A2_TSM_RESULT_H_

namespace scp {
struct TsmResult {
  std::vector<u_int32_t> vertices;
  double distance;
};
}  // namespace scp
#endif  // SCP_A2_TSM_RESULT_H_