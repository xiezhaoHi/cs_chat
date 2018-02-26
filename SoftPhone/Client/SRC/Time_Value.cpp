#ifndef TIME_VALUE_CPP
#define TIME_VALUE_CPP


#include "Time_Value.h"
#include <limits>
#include <iostream>
using namespace std;

Time_Value::operator timeval () const
{
  // OS_TRYJY ("Time_Value::operator timeval");
  return this->tv_;
}

Time_Value::operator FILETIME () const
{
  FILETIME file_time;
  // ACE_OS_TRACE ("ACE_Time_Value::operator FILETIME");


  ULARGE_INTEGER _100ns;
  _100ns.QuadPart = (((DWORDLONG) this->tv_.tv_sec * (10000 * 1000) +
                     this->tv_.tv_usec * 10) +
                     Time_Value::FILETIME_to_timval_skew);

  file_time.dwLowDateTime = _100ns.LowPart;
  file_time.dwHighDateTime = _100ns.HighPart;


  return file_time;
}

 void
Time_Value::set (const timeval &tv)
{
  // OS_TRYJY ("Time_Value::set");
  this->tv_.tv_sec = tv.tv_sec;
  this->tv_.tv_usec = tv.tv_usec;

  this->normalize ();
}


Time_Value::Time_Value (const struct timeval &tv)
  // : tv_ ()
{
  // OS_TRYJY ("Time_Value::Time_Value");
  this->set (tv);
}
Time_Value::Time_Value (const FILETIME &file_time)
{
  // // ACE_OS_TRACE ("ACE_Time_Value::ACE_Time_Value");
  this->set (file_time);
}


Time_Value::operator const timeval * () const
{
  // OS_TRYJY ("Time_Value::operator const timeval *");
  return (const timeval *) &this->tv_;
}
void Time_Value::set (const FILETIME &file_time)
{
  //  Initializes the ACE_Time_Value object from a Win32 FILETIME

  // Don't use a struct initializer, gcc don't like it.
  ULARGE_INTEGER _100ns;
  _100ns.LowPart = file_time.dwLowDateTime;
  _100ns.HighPart = file_time.dwHighDateTime;

  _100ns.QuadPart -= Time_Value::FILETIME_to_timval_skew;

  // Convert 100ns units to seconds;
  this->tv_.tv_sec = (long)(_100ns.QuadPart / (10000 * 1000));
  // Convert remainder to microseconds;
  this->tv_.tv_usec = (suseconds_t) ((_100ns.QuadPart % (10000 * 1000)) / 10);

  this->normalize ();
}

 void
Time_Value::set (time_t sec, suseconds_t usec)
{
  // OS_TRYJY ("Time_Value::set");

  this->tv_.tv_sec = sec;

  this->tv_.tv_usec = usec;

  this->normalize ();
}

 void
Time_Value::set (double d)
{
  // OS_TRYJY ("Time_Value::set");
  long l = (long) d;
  this->tv_.tv_sec = l;
  this->tv_.tv_usec = (suseconds_t) ((d - (double) l) * ONE_SECOND_IN_USECS + .5);
  this->normalize ();
}

// Initializes a timespec_t.  Note that this approach loses precision
// since it converts the nano-seconds into micro-seconds.  But then
// again, do any real systems have nano-second timer precision?!



Time_Value::Time_Value (void)
  // : tv_ ()
{
  // OS_TRYJY ("Time_Value::Time_Value");
  this->set (0, 0);
}


Time_Value::Time_Value (time_t sec, suseconds_t usec)
{
  // OS_TRYJY ("Time_Value::Time_Value");
  this->set (sec, usec);
}

// Returns number of seconds.

time_t
Time_Value::sec (void) const
{
  // OS_TRYJY ("Time_Value::sec");
  return this->tv_.tv_sec;
}

// Sets the number of seconds.

 void
Time_Value::sec (time_t sec)
{
  // OS_TRYJY ("Time_Value::sec");
  this->tv_.tv_sec = sec;
}

// Converts from Time_Value format into milli-seconds format.

 unsigned long
Time_Value::msec (void) const
{
  // OS_TRYJY ("Time_Value::msec");
  return this->tv_.tv_sec * 1000 + this->tv_.tv_usec / 1000;
}


// Converts from milli-seconds format into Time_Value format.

 void
Time_Value::msec (long milliseconds)
{
  // OS_TRYJY ("Time_Value::msec");
  // Convert millisecond units to seconds;
  this->tv_.tv_sec = milliseconds / 1000;
  // Convert remainder to microseconds;
  this->tv_.tv_usec = (milliseconds - (this->tv_.tv_sec * 1000)) * 1000;
}

// Returns number of micro-seconds.

 suseconds_t
Time_Value::usec (void) const
{
  // OS_TRYJY ("Time_Value::usec");
  return this->tv_.tv_usec;
}

// Sets the number of micro-seconds.

 void
Time_Value::usec (suseconds_t usec)
{
  // OS_TRYJY ("Time_Value::usec");
  this->tv_.tv_usec = usec;
}


 Time_Value
operator * (double d, const Time_Value &tv)
{
  return Time_Value (tv) *= d;
}

 Time_Value
operator * (const Time_Value &tv, double d)
{
  return Time_Value (tv) *= d;
}

// True if tv1 > tv2.
// bool
//operator > (const Time_Value &tv1,
//            const Time_Value &tv2)
//{
//  // OS_TRYJY ("operator >");
//  if (tv1.sec () > tv2.sec ())
//    return 1;
//  else if (tv1.sec () == tv2.sec ()
//           && tv1.usec () > tv2.usec ())
//    return 1;
//  else
//    return 0;
//}


// Add TV to this.

 Time_Value &
Time_Value::operator+= (const Time_Value &tv)
{
  // OS_TRYJY ("Time_Value::operator+=");
  this->sec (this->sec () + tv.sec ());
  this->usec (this->usec () + tv.usec ());
  this->normalize ();
  return *this;
}

 Time_Value &
Time_Value::operator+= (time_t tv)
{
  // OS_TRYJY ("Time_Value::operator+=");
  this->sec (this->sec () + tv);
  return *this;
}

 Time_Value &
Time_Value::operator= (const Time_Value &tv)
{
  // OS_TRYJY ("Time_Value::operator=");
  this->sec (tv.sec ());
  this->usec (tv.usec ());
  return *this;
}

 Time_Value &
Time_Value::operator= (time_t tv)
{
  // OS_TRYJY ("Time_Value::operator=");
  this->sec (tv);
  this->usec (0);
  return *this;
}

// Subtract TV to this.

 Time_Value &
Time_Value::operator-= (const Time_Value &tv)
{
  // OS_TRYJY ("Time_Value::operator-=");
  this->sec (this->sec () - tv.sec ());
  this->usec (this->usec () - tv.usec ());
  this->normalize ();
  return *this;
}

 Time_Value &
Time_Value::operator-= (time_t tv)
{
  // OS_TRYJY ("Time_Value::operator-=");
  this->sec (this->sec () - tv);
  return *this;
}



// Static constant representing `zero-time'.
// Note: this object requires static construction.
const Time_Value Time_Value::zero;

// Constant for maximum time representable.  Note that this time
// is not intended for use with select () or other calls that may
// have *their own* implementation-specific maximum time representations.
// Its primary use is in time computations such as those used by the
// dynamic subpriority strategies in the Dynamic_Message_Queue class.
// Note: this object requires static construction.
// Note: on platforms without std::numeric_limits<>, we assume time_t is
// a long, the historical type used for time.
const Time_Value Time_Value::max_time (LONG_MAX,ONE_SECOND_IN_USECS - 1);
const DWORDLONG Time_Value::FILETIME_to_timval_skew =0x19db1ded53e8000;


Time_Value
Time_Value::operator ++ (int)
{
  // OS_TRYJY ("Time_Value::operator ++ (int)");
  Time_Value tv (*this);
  ++*this;
  return tv;
}

Time_Value &
Time_Value::operator ++ (void)
{
  // OS_TRYJY ("Time_Value::operator ++ (void)");
  this->usec (this->usec () + 1);
  this->normalize ();
  return *this;
}

// Decrement microseconds (the only reason this is here is / to allow
// the use of Atomic_Op with Time_Value).

Time_Value
Time_Value::operator -- (int)
{
  // OS_TRYJY ("Time_Value::operator -- (int)");
  Time_Value tv (*this);
  --*this;
  return tv;
}

Time_Value &
Time_Value::operator -- (void)
{
  // OS_TRYJY ("Time_Value::operator -- (void)");
  this->usec (this->usec () - 1);
  this->normalize ();
  return *this;
}

bool Time_Value::operator == (const Time_Value &tv2)
{
	 return sec () == tv2.sec ()
    && usec () == tv2.usec ();
}

bool Time_Value::operator != (const Time_Value &tv2)
{
	 return !(*this == tv2); 
}

bool Time_Value::operator > (const Time_Value &tv2)
{
  // OS_TRYJY ("operator >");
  if (this->sec () > tv2.sec ())
    return true;
  else if (this->sec () == tv2.sec ()&& usec () > tv2.usec ())
    return true;
  else
    return false;
}

bool Time_Value::operator < (const Time_Value &tv2)
{
	 return !(*this > tv2)&& *this!=tv2; 
}

bool Time_Value::operator >= (const Time_Value &tv2)
{
	 return (*this == tv2)|| *this > tv2; 
}
bool Time_Value::operator <= (const Time_Value &tv2)
{
	 return !(*this == tv2) || *this  <tv2; 
}

Time_Value Time_Value::operator + (const Time_Value &tv2)
{
  // OS_TRYJY ("operator +");
  Time_Value sum (*this);
  sum += tv2;

  return sum;
}
Time_Value Time_Value::operator - (const Time_Value &tv2)
{
  // OS_TRYJY ("operator +");
  Time_Value sum (*this);
  sum -= tv2;
  return sum;
}





void
Time_Value::dump (void) const
{
#ifdef _DEBUG
	cout<<"second:\t"<<(tv_.tv_sec)<<endl;
	cout<<"suseconds:\t"<<(tv_.tv_usec)<<endl;

#endif
}

void
Time_Value::normalize (void)
{
  // // OS_TRYJY ("Time_Value::normalize");
  // From Hans Rohnert...

  if (this->tv_.tv_usec >= ONE_SECOND_IN_USECS)
    {
      /*! \todo This loop needs some optimization.
       */
      do
        {
          ++this->tv_.tv_sec;
          this->tv_.tv_usec -= ONE_SECOND_IN_USECS;
        }
      while (this->tv_.tv_usec >= ONE_SECOND_IN_USECS);
    }
  else if (this->tv_.tv_usec <= -ONE_SECOND_IN_USECS)
    {
      /*! \todo This loop needs some optimization.
       */
      do
        {
          --this->tv_.tv_sec;
          this->tv_.tv_usec += ONE_SECOND_IN_USECS;
        }
      while (this->tv_.tv_usec <= -ONE_SECOND_IN_USECS);
    }

  if (this->tv_.tv_sec >= 1 && this->tv_.tv_usec < 0)
    {
      --this->tv_.tv_sec;
      this->tv_.tv_usec += ONE_SECOND_IN_USECS;
    }

  else if (this->tv_.tv_sec < 0 && this->tv_.tv_usec > 0)
    {
      ++this->tv_.tv_sec;
      this->tv_.tv_usec -= ONE_SECOND_IN_USECS;
    }

}


Time_Value &
Time_Value::operator *= (double d)
{
  // double is long enough (16 digits) to not lose the accuracy.
  double time_total =
    (this->sec ()
     + static_cast<double> (this->usec ()) / ONE_SECOND_IN_USECS) * d;

  // shall we saturate the result?

  static const double max_int = LONG_MAX + 0.999999;
  static const double min_int = LONG_MIN - 0.999999;

  if (time_total > max_int)
    time_total = max_int;
  if (time_total < min_int)
    time_total = min_int;

  const time_t time_sec = static_cast<time_t> (time_total);

  time_total -= time_sec;
  time_total *= ONE_SECOND_IN_USECS;

  suseconds_t time_usec = static_cast<suseconds_t> (time_total);

  // round up the result to save the last usec
  if (time_usec > 0 && (time_total - time_usec) >= 0.5)
    ++time_usec;
  else if (time_usec < 0 && (time_total - time_usec) <= -0.5)
    --time_usec;

  this->set (time_sec, time_usec);

  return *this;
}

Time_Value Time_Value::GetTimeofday()
{
  SYSTEMTIME tsys;
  FILETIME   tfile;
  ::GetSystemTime (&tsys);
  ::SystemTimeToFileTime (&tsys, &tfile);
  return Time_Value (tfile);
}

#endif /*TIME_VALUE_CPP*/

