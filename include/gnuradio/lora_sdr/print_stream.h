#ifndef INCLUDED_LORA_SDR_PRINT_STREAM_H
#define INCLUDED_LORA_SDR_PRINT_STREAM_H

#include <gnuradio/lora_sdr/api.h>
#include <gnuradio/sync_block.h>
#include <string>

namespace gr {
namespace lora_sdr {

/*!
 * \brief <+description of block+>
 * \ingroup lora_sdr
 *
 */
class LORA_SDR_API print_stream : virtual public gr::sync_block {
public:
  typedef std::shared_ptr<print_stream> sptr;


  static sptr make(std::string string_type, int vlen);
};

} // namespace lora_sdr
} // namespace gr

#endif /* INCLUDED_LORA_SDR_PRINT_STREAM_H */
