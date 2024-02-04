#include "print_stream_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/types.h> 

namespace gr {
namespace lora_sdr {

size_t size_from_string_type(const std::string& string_type) {
    if (string_type == "complex") {
        return sizeof(gr_complex);
    } else if (string_type == "float") {
        return sizeof(float);
    } else if (string_type == "int") {
        return sizeof(int);
    } else if (string_type == "short") {
        return sizeof(short);
    } else if (string_type == "byte") {
        return sizeof(char);
    } else {
        throw std::runtime_error("Unsupported type: " + string_type);
    }
}

//create a function that returns a lambda function
std::function<void(const char*, char*)> create_cast_function_from_string_type(const std::string& string_type) {
    if (string_type == "complex") {
        return [](const char* in, char* out) {
            auto in_c = reinterpret_cast<const gr_complex*>(in);
            auto out_c = reinterpret_cast<gr_complex*>(out);
            *out_c = *in_c;
        };
    } else if (string_type == "float") {
        return [](const char* in, char* out) {
            auto in_f = reinterpret_cast<const float*>(in);
            auto out_f = reinterpret_cast<float*>(out);
            *out_f = *in_f;
        };
    } else if (string_type == "int") {
        return [](const char* in, char* out) {
            auto in_i = reinterpret_cast<const int*>(in);
            auto out_i = reinterpret_cast<int*>(out);
            *out_i = *in_i;
        };
    } else if (string_type == "short") {
        return [](const char* in, char* out) {
            auto in_s = reinterpret_cast<const short*>(in);
            auto out_s = reinterpret_cast<short*>(out);
            *out_s = *in_s;
        };
    } else if (string_type == "byte") {
        return [](const char* in, char* out) {
            auto in_b = reinterpret_cast<const char*>(in);
            auto out_b = reinterpret_cast<char*>(out);
            *out_b = *in_b;
        };
    } else {
        throw std::runtime_error("Unsupported type: " + string_type);
    }
}

print_stream::sptr print_stream::make(std::string string_type, int vlen) {
  return gnuradio::make_block_sptr<print_stream_impl>(string_type, vlen);
}

print_stream_impl::print_stream_impl(std::string string_type, int vlen)
    : gr::sync_block("print_stream",
                     gr::io_signature::make(1 /* min inputs */,
                                            1 /* max inputs */,
                                            size_from_string_type(string_type) * vlen),
                     gr::io_signature::make(0, 0, 0)),
      _cast_function(create_cast_function_from_string_type(string_type)),
      _vlen(vlen) {}

print_stream_impl::~print_stream_impl() {}

int print_stream_impl::work(int noutput_items,
                            gr_vector_const_void_star &input_items,
                            gr_vector_void_star &output_items) {

  // const auto in = static_cast<const char*>(input_items[0]); // Cast to char* for byte access
  //  // Print each item based on d_itemsize and d_vlen
  // for (int i = 0; i < noutput_items; ++i) {
  //   // You'll need to implement the logic here to handle different types and vector lengths
  //   // For now, we'll simply print as if they were bytes
  //   std::cout << "Data: ";
  //   for (int j = 0; j < d_vlen; ++j) {
  //     // Adjust this line according to how you want to interpret and print your data
  //     std::cout << in[i * d_itemsize * d_vlen + j] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  consume_each(noutput_items); //output items = input items

  return 0; //sink
}

} /* namespace lora_sdr */
} /* namespace gr */
