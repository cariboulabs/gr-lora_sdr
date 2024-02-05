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

print_stream::sptr print_stream::make(std::string string_type, int vlen) {
  return gnuradio::make_block_sptr<print_stream_impl>(string_type, vlen);
}

print_stream_impl::print_stream_impl(std::string string_type, int vlen)
    : gr::sync_block("print_stream",
                     gr::io_signature::make(1 /* min inputs */,
                                            1 /* max inputs */,
                                            size_from_string_type(string_type) * vlen),
                     gr::io_signature::make(0, 0, 0)),
        _vlen(vlen),
        _string_type(string_type)
        {}

print_stream_impl::~print_stream_impl() {}

int print_stream_impl::work(int noutput_items,
                            gr_vector_const_void_star &input_items,
                            gr_vector_void_star &output_items) {

  void* in = (void*)input_items[0]; // Cast to for byte access
  if (_string_type == "complex") {
    std::complex<float>* in_c = reinterpret_cast<std::complex<float>*>(in);
    for (int i = 0; i < noutput_items; ++i) {
        for (int j = 0; j < _vlen; ++j) {
            printf("(%f %f) \n", in_c[i * _vlen + j].real(), in_c[i * _vlen + j].imag());
        }
    }

  } else if (_string_type == "float") {
    float* in_c = reinterpret_cast<float*>(in);
    for (int i = 0; i < noutput_items; ++i) {
        for (int j = 0; j < _vlen; ++j) {
            printf("%f \n", in_c[i * _vlen + j]);
        }
    }
  } else if (_string_type == "int") {
    int* in_c = reinterpret_cast<int*>(in);
    for (int i = 0; i < noutput_items; ++i) {
        for (int j = 0; j < _vlen; ++j) {
            printf("%d \n", in_c[i * _vlen + j]);
        }
    }
  } else if (_string_type == "short") {
    short* in_c = reinterpret_cast<short*>(in);
    for (int i = 0; i < noutput_items; ++i) {
        for (int j = 0; j < _vlen; ++j) {
            printf("%d \n", in_c[i * _vlen + j]);
        }
    }
  } else if (_string_type == "byte") {
    uint8_t* in_c = reinterpret_cast<uint8_t*>(in);
    for (int i = 0; i < noutput_items; ++i) {
        for (int j = 0; j < _vlen; ++j) {
            printf("%d \n", in_c[i * _vlen + j]);
        }
    }
  } else {
  }
  consume_each(noutput_items); //output items = input items

  return 0; //sink
}

} /* namespace lora_sdr */
} /* namespace gr */
