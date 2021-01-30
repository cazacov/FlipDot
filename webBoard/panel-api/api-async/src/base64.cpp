#include <string>
#include <vector>

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::string base64encode(const std::vector<uint8_t> &bytes) {
std::string ret;
  int i = 0;
  int j = 0;
  uint8_t data_array_3[3];
  unsigned char char_array_4[4];

  for (auto &data : bytes) {
    data_array_3[i++] = data;
    if (i == 3) {
      char_array_4[0] = (data_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((data_array_3[0] & 0x03) << 4) + ((data_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((data_array_3[1] & 0x0f) << 2) + ((data_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = data_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      data_array_3[j] = '\0';

    char_array_4[0] = (data_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((data_array_3[0] & 0x03) << 4) + ((data_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((data_array_3[1] & 0x0f) << 2) + ((data_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = data_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';
  }

  return ret;
}