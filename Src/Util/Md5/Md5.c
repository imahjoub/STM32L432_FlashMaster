
/*************************** HEADER FILES ***************************/
#include <stdlib.h>
#include <string.h>
#include <Util/Md5/Md5.h>

/**************************** MD5 VARIABLES ****************************/
static uint8_t  Md5_TransformBlock[64U];
static uint32_t Md5_DataLen;
static uint64_t Md5_BitLen;
static uint32_t Md5_State[4U];

/****************************** MACROS & FUNCTIONS PROTOTYPES ******************************/
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) (y ^ (x | ~z))

#define FF(a, b, c, d, m, s, t) { a += F(b, c, d) + m + t; a = b + ROTLEFT(a,s); }
#define GG(a, b, c, d, m, s, t) { a += G(b, c, d) + m + t; a = b + ROTLEFT(a,s); }
#define HH(a, b, c, d, m, s, t) { a += H(b, c, d) + m + t; a = b + ROTLEFT(a,s); }
#define II(a, b, c, d, m, s, t) { a += I(b, c, d) + m + t; a = b + ROTLEFT(a,s); }

static inline uint32_t ROTLEFT(uint32_t a, uint32_t b);

static void Md5_Init(void);
static void Md5_Update(const uint8_t* Message, size_t MessageLength);
static void Md5_Transform(const uint8_t* TransformBuff);
static void Md5_Final(uint8_t* Md5_Result);

/*********************** FUNCTION DEFINITIONS ***********************/

static inline uint32_t ROTLEFT(uint32_t a, uint32_t b)
{
  return ((uint32_t)(a << b) | (uint32_t)(a >> (32U - b)));
}

static void Md5_Transform(const uint8_t* TransformBlock)
{
  uint32_t a     = 0U;
  uint32_t b     = 0U;
  uint32_t c     = 0U;
  uint32_t d     = 0U;
  uint32_t i     = 0U;
  uint32_t j     = 0U;
  uint32_t m[16] = {0U};

  /*  MD5 specifies big endian byte order, but this implementation assumes a little */
  /*  endian byte order CPU. Reverse all the bytes upon input, and re-reverse them */
  /*  on output (in Md5_Final()). */
  for (i = 0U, j = 0U; i < 16U; ++i, j += 4U)
  {
    m[i] = (uint32_t)(((uint32_t)TransformBlock[j]) + ((uint32_t)TransformBlock[j + 1U] << 8U) + ((uint32_t)TransformBlock[j + 2U] << 16U) + ((uint32_t)TransformBlock[j + 3U] << 24U));
  }

  a =   Md5_State[0U];
  b =   Md5_State[1U];
  c =   Md5_State[2U];
  d =   Md5_State[3U];

  FF(a, b, c, d, m[ 0U], UINT8_C( 7), UINT32_C(0xD76AA478));
  FF(d, a, b, c, m[ 1U], UINT8_C(12), UINT32_C(0xE8C7B756));
  FF(c, d, a, b, m[ 2U], UINT8_C(17), UINT32_C(0x242070DB));
  FF(b, c, d, a, m[ 3U], UINT8_C(22), UINT32_C(0xC1BDCEEE));
  FF(a, b, c, d, m[ 4U], UINT8_C( 7), UINT32_C(0xF57C0FAF));
  FF(d, a, b, c, m[ 5U], UINT8_C(12), UINT32_C(0x4787C62A));
  FF(c, d, a, b, m[ 6U], UINT8_C(17), UINT32_C(0xA8304613));
  FF(b, c, d, a, m[ 7U], UINT8_C(22), UINT32_C(0xFD469501));
  FF(a, b, c, d, m[ 8U], UINT8_C( 7), UINT32_C(0x698098D8));
  FF(d, a, b, c, m[ 9U], UINT8_C(12), UINT32_C(0x8B44F7AF));
  FF(c, d, a, b, m[10U], UINT8_C(17), UINT32_C(0xFFFF5BB1));
  FF(b, c, d, a, m[11U], UINT8_C(22), UINT32_C(0x895CD7BE));
  FF(a, b, c, d, m[12U], UINT8_C( 7), UINT32_C(0x6B901122));
  FF(d, a, b, c, m[13U], UINT8_C(12), UINT32_C(0xFD987193));
  FF(c, d, a, b, m[14U], UINT8_C(17), UINT32_C(0xA679438E));
  FF(b, c, d, a, m[15U], UINT8_C(22), UINT32_C(0x49B40821));

  GG(a, b, c, d, m[ 1U], UINT8_C( 5), UINT32_C(0xF61E2562));
  GG(d, a, b, c, m[ 6U], UINT8_C( 9), UINT32_C(0xC040B340));
  GG(c, d, a, b, m[11U], UINT8_C(14), UINT32_C(0x265E5A51));
  GG(b, c, d, a, m[ 0U], UINT8_C(20), UINT32_C(0xE9B6C7AA));
  GG(a, b, c, d, m[ 5U], UINT8_C( 5), UINT32_C(0xD62F105D));
  GG(d, a, b, c, m[10U], UINT8_C( 9), UINT32_C(0x02441453));
  GG(c, d, a, b, m[15U], UINT8_C(14), UINT32_C(0xD8A1E681));
  GG(b, c, d, a, m[ 4U], UINT8_C(20), UINT32_C(0xE7D3FBC8));
  GG(a, b, c, d, m[ 9U], UINT8_C( 5), UINT32_C(0x21E1CDE6));
  GG(d, a, b, c, m[14U], UINT8_C( 9), UINT32_C(0xC33707D6));
  GG(c, d, a, b, m[ 3U], UINT8_C(14), UINT32_C(0xF4D50D87));
  GG(b, c, d, a, m[ 8U], UINT8_C(20), UINT32_C(0x455A14ED));
  GG(a, b, c, d, m[13U], UINT8_C( 5), UINT32_C(0xA9E3E905));
  GG(d, a, b, c, m[ 2U], UINT8_C( 9), UINT32_C(0xFCEFA3F8));
  GG(c, d, a, b, m[ 7U], UINT8_C(14), UINT32_C(0x676F02D9));
  GG(b, c, d, a, m[12U], UINT8_C(20), UINT32_C(0x8D2A4C8A));

  HH(a, b, c, d, m[ 5U], UINT8_C( 4), UINT32_C(0xFFFA3942));
  HH(d, a, b, c, m[ 8U], UINT8_C(11), UINT32_C(0x8771F681));
  HH(c, d, a, b, m[11U], UINT8_C(16) ,UINT32_C(0x6D9D6122));
  HH(b, c, d, a, m[14U], UINT8_C(23), UINT32_C(0xFDE5380C));
  HH(a, b, c, d, m[ 1U], UINT8_C( 4), UINT32_C(0xA4BEEA44));
  HH(d, a, b, c, m[ 4U], UINT8_C(11), UINT32_C(0x4BDECFA9));
  HH(c, d, a, b, m[ 7U], UINT8_C(16), UINT32_C(0xF6BB4B60));
  HH(b, c, d, a, m[10U], UINT8_C(23), UINT32_C(0xBEBFBC70));
  HH(a, b, c, d, m[13U], UINT8_C( 4), UINT32_C(0x289B7EC6));
  HH(d, a, b, c, m[ 0U], UINT8_C(11), UINT32_C(0xEAA127FA));
  HH(c, d, a, b, m[ 3U], UINT8_C(16), UINT32_C(0xD4EF3085));
  HH(b, c, d, a, m[ 6U], UINT8_C(23), UINT32_C(0x04881D05));
  HH(a, b, c, d, m[ 9U], UINT8_C( 4), UINT32_C(0xD9D4D039));
  HH(d, a, b, c, m[12U], UINT8_C(11), UINT32_C(0xE6DB99E5));
  HH(c, d, a, b, m[15U], UINT8_C(16), UINT32_C(0x1FA27CF8));
  HH(b, c, d, a, m[ 2U], UINT8_C(23), UINT32_C(0xC4AC5665));

  II(a, b, c, d, m[ 0U], UINT8_C( 6), UINT32_C(0xF4292244));
  II(d, a, b, c, m[ 7U], UINT8_C(10), UINT32_C(0x432AFF97));
  II(c, d, a, b, m[14U], UINT8_C(15), UINT32_C(0xAB9423A7));
  II(b, c, d, a, m[ 5U], UINT8_C(21), UINT32_C(0xFC93A039));
  II(a, b, c, d, m[12U], UINT8_C( 6), UINT32_C(0x655B59C3));
  II(d, a, b, c, m[ 3U], UINT8_C(10), UINT32_C(0x8F0CCC92));
  II(c, d, a, b, m[10U], UINT8_C(15), UINT32_C(0xFFEFF47D));
  II(b, c, d, a, m[ 1U], UINT8_C(21), UINT32_C(0x85845DD1));
  II(a, b, c, d, m[ 8U], UINT8_C( 6), UINT32_C(0x6FA87E4F));
  II(d, a, b, c, m[15U], UINT8_C(10), UINT32_C(0xFE2CE6E0));
  II(c, d, a, b, m[ 6U], UINT8_C(15), UINT32_C(0xA3014314));
  II(b, c, d, a, m[13U], UINT8_C(21), UINT32_C(0x4E0811A1));
  II(a, b, c, d, m[ 4U], UINT8_C( 6), UINT32_C(0xF7537E82));
  II(d, a, b, c, m[11U], UINT8_C(10), UINT32_C(0xBD3AF235));
  II(c, d, a, b, m[ 2U], UINT8_C(15), UINT32_C(0x2AD7D2BB));
  II(b, c, d, a, m[ 9U], UINT8_C(21), UINT32_C(0xEB86D391));

  Md5_State[0U] += a;
  Md5_State[1U] += b;
  Md5_State[2U] += c;
  Md5_State[3U] += d;
}

static void Md5_Init(void)
{
  Md5_DataLen  = UINT32_C(0);
  Md5_BitLen   = UINT64_C(0);
  Md5_State[0] = UINT32_C(0x67452301);
  Md5_State[1] = UINT32_C(0xEFCDAB89);
  Md5_State[2] = UINT32_C(0x98BADCFE);
  Md5_State[3] = UINT32_C(0x10325476);
}

static void Md5_Update(const uint8_t* Message, size_t MessageLength)
{
  for(size_t i = 0U; i < MessageLength; ++i)
  {
    Md5_TransformBlock[Md5_DataLen] = Message[i];
    ++Md5_DataLen;

    if (Md5_DataLen == 64U)
    {
      Md5_Transform(Md5_TransformBlock);
      Md5_BitLen += 512U;
      Md5_DataLen = 0U;
    }
  }
}

static void Md5_Final(uint8_t* Md5_Result)
{
  size_t i = Md5_DataLen;

  /* Pad whatever Md5_TransformBlock is left in the buffer. */
  if(Md5_DataLen < 56U)
  {
    Md5_TransformBlock[i++] = 0x80U;

    while (i < 56U)
    {
      Md5_TransformBlock[i++] = 0x00U;
    }
  }
  else if(Md5_DataLen >= 56U)
  {
    Md5_TransformBlock[i++] = 0x80U;

    while(i < 64U) { Md5_TransformBlock[i++] = 0x00U; }

    Md5_Transform(Md5_TransformBlock);

    memset(Md5_TransformBlock, 0U, 56U);
  }

  /* Append to the padding the total message's length in bits and transform.*/
  Md5_BitLen             += (uint64_t)(Md5_DataLen * 8U);
  Md5_TransformBlock[56U] = (uint8_t) (Md5_BitLen >>  0U);
  Md5_TransformBlock[57U] = (uint8_t) (Md5_BitLen >>  8U);
  Md5_TransformBlock[58U] = (uint8_t) (Md5_BitLen >> 16U);
  Md5_TransformBlock[59U] = (uint8_t) (Md5_BitLen >> 24U);
  Md5_TransformBlock[60U] = (uint8_t) (Md5_BitLen >> 32U);
  Md5_TransformBlock[61U] = (uint8_t) (Md5_BitLen >> 40U);
  Md5_TransformBlock[62U] = (uint8_t) (Md5_BitLen >> 48U);
  Md5_TransformBlock[63U] = (uint8_t) (Md5_BitLen >> 56U);
  Md5_Transform(Md5_TransformBlock);

  /*  Since this implementation uses little endian byte ordering and MD uses big endian, */
  /*  reverse all the bytes when copying the final Md5_State to the output hash. */
  for (i = 0U; i < 4U; ++i)
  {
    Md5_Result[i +  0U] = (Md5_State[0U] >> (i * 8U) & 0x000000FFU);
    Md5_Result[i +  4U] = (Md5_State[1U] >> (i * 8U) & 0x000000FFU);
    Md5_Result[i +  8U] = (Md5_State[2U] >> (i * 8U) & 0x000000FFU);
    Md5_Result[i + 12U] = (Md5_State[3U] >> (i * 8U) & 0x000000FFU);
  }
}

void Md5_Calculate(const uint8_t* MsgPtr, const size_t Msglength, uint8_t* Md5Result)
{
  /* Initialize */
  Md5_Init();

  /* Md5_Update */
  Md5_Update(MsgPtr, Msglength);

  /* finalize */
  Md5_Final(Md5Result);
}

bool Md5_Check(const uint8_t* Md5Result, const uint8_t* Md5Check)
{
  bool Md5_CheckIsOk = false;

  Md5_CheckIsOk = (memcmp(Md5Check, Md5Result, MD5_BLOCK_SIZE) == 0U);

  return Md5_CheckIsOk;
}

