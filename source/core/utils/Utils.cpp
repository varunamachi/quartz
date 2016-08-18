/*******************************************************************************
 * Copyright (c) 2014 Varuna L Amachi. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#include <QTime>
#include "Utils.h"

using namespace Tanyatu;

Data::MediaRating Utils::getRatingFromInt( int rating )
{
    switch(rating) {
    case 0: return Data::Rating_None;
    case 1: return Data::Rating_Bad;
    case 2: return Data::Rating_Average;
    case 3: return Data::Rating_Good;
    case 4: return Data::Rating_VeryGood;
    case 5: return Data::Rating_Excellent;
    }
    return Data::Rating_None;
}


QString Utils::getStringTime(int timeInSeconds) {
        int hours = timeInSeconds / (60 * 60);
        int min   = timeInSeconds / 60;
        int sec   = timeInSeconds % 60;
        QTime displayTime(hours , min, sec);
        return (hours == 0? displayTime.toString("mm:ss") :
                            displayTime.toString("hh:mm:ss"));
}


//QImage* Utils::imageForTrack( Data::AudioTrack *track )
//{
//    QImage *image = 0;
//    if( track->url().isLocalFile() )
//    {
//        TagLib::MPEG::File tagFile( track->url().toLocalFile()
//                                    .toStdString().c_str() );
//        if( tagFile.isValid() && tagFile.ID3v2Tag() ) {
//            TagLib::ID3v2::Tag *tag = tagFile.ID3v2Tag();
//            TagLib::ID3v2::FrameList l = tag->frameList("APIC");
//            if( ! l.isEmpty() ) {
//                image = new QImage();
//                TagLib::ID3v2::AttachedPictureFrame *frame =
//                        static_cast< TagLib::ID3v2::AttachedPictureFrame * >(
//                            l.front());
//                image->loadFromData( (const uchar *)
//                            frame->picture().data(), frame->picture().size());
//            }
//        }
//    }
//    return image;
//}

