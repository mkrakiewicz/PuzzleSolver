#ifndef DBG_H
#define DBG_H

#include <QDebug>
#include <chrono>

class Avg
{
   long int sum;
   long int count;

   std::chrono::high_resolution_clock::time_point last;
   bool started;
public:
   Avg():sum(0),count(0),last(), started(false)
   {

   }

   void start()
   {
       last = std::chrono::high_resolution_clock::now();
       started = true;
   }

   void stop()
   {

       if (started) {
           auto now = std::chrono::high_resolution_clock::now();

           auto dur = now - last;
           auto ms = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
           sum+=ms;
           count++;
           started = false;
       }
   }

   float getAvg()
   {
//       qDebug() << "Sum : " << sum << " COUNT : " << count;
       if (count == 0) return 0.f;
       return (float)sum/(float)count;
    }
};

#endif // DBG_H
