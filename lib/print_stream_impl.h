#ifndef INCLUDED_LORA_SDR_PRINT_STREAM_IMPL_H
#define INCLUDED_LORA_SDR_PRINT_STREAM_IMPL_H

#include <gnuradio/lora_sdr/print_stream.h>

namespace gr {
namespace lora_sdr {

class print_stream_impl : public print_stream {
private:
  int _vlen;
  std::string _string_type;

public:
  print_stream_impl(std::string string_type, int vlen);
  ~print_stream_impl();

  // Where all the action really happens
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace lora_sdr
} // namespace gr

#endif /* INCLUDED_LORA_SDR_PRINT_STREAM_IMPL_H */
