#include "print_stream_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace lora_sdr {

print_stream::sptr print_stream::make(size_t itemsize, int vlen) {
  return gnuradio::make_block_sptr<print_stream_impl>(itemsize, vlen);
}

print_stream_impl::print_stream_impl(size_t itemsize, int vlen)
    : gr::sync_block("print_stream",
                     gr::io_signature::make(1 /* min inputs */,
                                            1 /* max inputs */,
                                            itemsize * vlen),
                     gr::io_signature::make(0, 0, 0)),
      d_itemsize(itemsize),
      d_vlen(vlen) {}

print_stream_impl::~print_stream_impl() {}

int print_stream_impl::work(int noutput_items,
                            gr_vector_const_void_star &input_items,
                            gr_vector_void_star &output_items) {

  const auto in = static_cast<const char*>(input_items[0]); // Cast to char* for byte access
   // Print each item based on d_itemsize and d_vlen
  for (int i = 0; i < noutput_items; ++i) {
    // You'll need to implement the logic here to handle different types and vector lengths
    // For now, we'll simply print as if they were bytes
    std::cout << "Data: ";
    for (int j = 0; j < d_vlen; ++j) {
      // Adjust this line according to how you want to interpret and print your data
      std::cout << in[i * d_itemsize * d_vlen + j] << " ";
    }
    std::cout << std::endl;
  }

  consume_each(noutput_items); //output items = input items

  return 0; //sink
}

} /* namespace lora_sdr */
} /* namespace gr */
