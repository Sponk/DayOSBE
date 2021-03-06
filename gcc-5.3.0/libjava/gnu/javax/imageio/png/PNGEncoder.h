
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_javax_imageio_png_PNGEncoder__
#define __gnu_javax_imageio_png_PNGEncoder__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace javax
    {
      namespace imageio
      {
        namespace png
        {
            class PNGEncoder;
            class PNGHeader;
            class PNGICCProfile;
            class PNGPalette;
        }
      }
    }
  }
  namespace java
  {
    namespace awt
    {
      namespace image
      {
          class BufferedImage;
      }
    }
  }
}

class gnu::javax::imageio::png::PNGEncoder : public ::java::lang::Object
{

public:
  PNGEncoder(::java::awt::image::BufferedImage *);
  virtual ::gnu::javax::imageio::png::PNGHeader * getHeader();
  virtual ::gnu::javax::imageio::png::PNGPalette * getPalette();
  virtual ::gnu::javax::imageio::png::PNGICCProfile * getProfile();
  virtual ::java::util::Vector * encodeImage();
private:
  void getRawData(::java::awt::image::BufferedImage *);
  static const jint defaultChunkSize = 8192;
  ::gnu::javax::imageio::png::PNGHeader * __attribute__((aligned(__alignof__( ::java::lang::Object)))) header;
  ::gnu::javax::imageio::png::PNGPalette * palette;
  jint stride;
  jint bpp;
  JArray< jbyte > * rawData;
  ::gnu::javax::imageio::png::PNGICCProfile * profile;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_javax_imageio_png_PNGEncoder__
