// -*- C++ -*-

//=============================================================================
/**
 *  @file    Time_Value.h
 *
 *  Time_Value.h,v 4.59 2006/02/10 10:37:02 jwillemsen Exp
 *
 *  @author Douglas C. Schmidt <schmidt@cs.wustl.edu>
 */
//=============================================================================

#ifndef TIME_VALUE_H
#define TIME_VALUE_H

#define Export

// Define some helpful constants.
// Not type-safe, and signed.  For backward compatibility.
#define ONE_SECOND_IN_MSECS 1000L			//∫¡√Î
#define ONE_SECOND_IN_USECS 1000000L		//Œ¢√Ó
#define ONE_SECOND_IN_NSECS 1000000000L		//ƒ…√Î

#include <windows.h>
#include <time.h>


typedef long suseconds_t;		//Œ¢√Ó

// ±º‰
class  Time_Value
{
public:
	static Time_Value GetTimeofday();

  /// Constant "0".
  static const Time_Value zero;

  /**
   * Constant for maximum time representable.  Note that this time is
   * not intended for use with <select> or other calls that may have
   * *their own* implementation-specific maximum time representations.
   * Its primary use is in time computations such as those used by the
   * dynamic subpriority strategies in the Dynamic_Message_Queue
   * class.
   */
  static const Time_Value max_time;
  static const DWORDLONG FILETIME_to_timval_skew ;

  // = Initialization methods.

  /// Default Constructor.
  Time_Value (void);

  // = Methods for converting to/from various time formats.

  /// Construct the Time_Value from a timeval.
  explicit  Time_Value (const struct timeval &t);
  explicit	Time_Value (time_t sec, suseconds_t usec);
  explicit Time_Value (const FILETIME &ft);

  /// Initializes the Time_Value from a double, which is assumed to be
  /// in second format, with any remainder treated as microseconds.
  void set (double d);

  /// Initializes the Time_Value from a timeval.
  void set (const timeval &t);
  void set (time_t sec, suseconds_t usec);
  void set (const FILETIME &file_time);

  /// Converts from Time_Value format into milli-seconds format.
  /**
   * @return Sum of second field (in milliseconds) and microsecond field
   *         (in milliseconds).  Note that this method can overflow if
   *         the second and microsecond field values are large, so use
   *         the msec (UINT64 &ms) method instead.
   *
   * @note The semantics of this method differs from the sec() and
   *       usec() methods.  There is no analogous "millisecond"
   *       component in an Time_Value.
   */
  unsigned long msec (void) const;


  /// Converts from milli-seconds format into Time_Value format.
  /**
   * @note The semantics of this method differs from the sec() and
   *       usec() methods.  There is no analogous "millisecond"
   *       component in an Time_Value.
   */
  void msec (long);


  /// Returns the value of the object as a timeval.
  operator timeval () const;

  /// Returns a pointer to the object as a timeval.
  operator const timeval *() const;


  operator FILETIME () const;
  /// Get seconds.
  /**
   * @return The second field/component of this Time_Value.
   *
   * @note The semantics of this method differs from the msec()
   *       method.
   */
  time_t sec (void) const;

  /// Set seconds.
  void sec (time_t sec);

  /// Set microseconds.
  void usec (suseconds_t usec);
  suseconds_t usec (void) const;
  // = The following arithmetic methods operate on Time_Value's.

 

  /// Add @a tv to this.
  Time_Value &operator += (const Time_Value &tv);

  /// Add @a tv to this.
  Time_Value &operator += (time_t tv);

  /// Assign @ tv to this
  Time_Value &operator = (const Time_Value &tv);

  /// Assign @ tv to this
  Time_Value &operator = (time_t tv);

  /// Subtract @a tv to this.
  Time_Value &operator -= (const Time_Value &tv);

  /// Substract @a tv to this.
  Time_Value &operator -= (time_t tv);


  bool	operator == (const Time_Value &tv2);
  bool  operator > (const Time_Value &tv2);
  bool  operator < (const Time_Value &tv2);
  bool	operator != (const Time_Value &tv2);
  bool  operator >= (const Time_Value &tv2);
  bool  operator <= (const Time_Value &tv2);
  Time_Value operator + (const Time_Value &tv2);
  Time_Value operator - (const Time_Value &tv2);
  /**
    \brief Multiply the time value by the @a d factor.
    \note The result of the operator is valid for results from range
    < (INT32_MIN, -999999), (INT32_MAX, 999999) >. Result
    outside this range are saturated to a limit.
     */
  Time_Value &operator *= (double d);

  /// Increment microseconds as postfix.
  /**
   * @note The only reason this is here is to allow the use of Atomic_Op
   * with Time_Value.
   */
  Time_Value operator++ (int);

  /// Increment microseconds as prefix.
  /**
   * @note The only reason this is here is to allow the use of Atomic_Op
   * with Time_Value.
   */
  Time_Value &operator++ (void);

  /// Decrement microseconds as postfix.
  /**
   * @note The only reason this is here is to allow the use of Atomic_Op
   * with Time_Value.
   */
  Time_Value operator-- (int);

  /// Decrement microseconds as prefix.
  /**
   * @note The only reason this is here is to allow the use of Atomic_Op
   * with Time_Value.
   */
  Time_Value &operator-- (void);


  /// True if @a tv1 < @a tv2.
  friend Export bool operator < (const Time_Value &tv1,
                                     const Time_Value &tv2);

  /// True if @a tv1 > @a tv2.
  friend Export bool operator > (const Time_Value &tv1,
                                     const Time_Value &tv2);

  /// True if @a tv1 <= @a tv2.
  friend Export bool operator <= (const Time_Value &tv1,
                                      const Time_Value &tv2);

  /// True if @a tv1 >= @a tv2.
  friend Export bool operator >= (const Time_Value &tv1,
                                      const Time_Value &tv2);

  /// True if @a tv1 == @a tv2.
  friend Export bool operator == (const Time_Value &tv1,
                                      const Time_Value &tv2);

  /// True if @a tv1 != @a tv2.
  friend Export bool operator != (const Time_Value &tv1,
                                      const Time_Value &tv2);

  //@{
  /// Multiplies the time value by @a d
  friend Export Time_Value operator * (double d,
                                               const Time_Value &tv);

  friend Export Time_Value operator * (const Time_Value &tv,
                                               double d);
  //@}

  /// Dump is a no-op.
  /**
   * The dump() method is a no-op.  It's here for backwards compatibility
   * only, but does not dump anything. Invoking logging methods here
   * violates layering restrictions in YJY because this class is part
   * of the OS layer and @c Log_Msg is at a higher level.
   */
  void dump (void) const;


private:
  /// Put the timevalue into a canonical form.
  void normalize (void);

  /// Store the values as a timeval.
  timeval tv_;
};

#endif /* TIME_VALUE_H */
