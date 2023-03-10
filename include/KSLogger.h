/**
 * @file KSLogger.h
 * 
 * @brief Header File for Library KSLogger
 * 
 * @details Provides functionality for logging in Arduino frameworks
 *   based on a video from Tomasz Tarnowski
 * 
 * @see https://github.com/JoachimKittelberger/KSLogger
 * 
 * @author Joachim Kittelberger <jkittelberger@kibesoft.de>
 * @date 03.02.2023
 * @version 1.00
 *
 * @todo
 *   - Add examples to library
 *   - publish library to PlatformIO
 * @bug
 *   - First Bug??
 */

/**
 * @copyright
 * Copyright (C) 2022 - 2023, KibeSoft - Joachim Kittelberger, (https://www.kibesoft.de)
 * All rights reserved
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     https://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _KSLogger_H
#define _KSLogger_H

// set default log level
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

// from RFC 5424
#define LOG_LEVEL_TRACE 0
#define LOG_LEVEL_DEBUG 100
#define LOG_LEVEL_INFO 200
#define LOG_LEVEL_NOTICE 250
#define LOG_LEVEL_WARNING 300
#define LOG_LEVEL_ERROR 400
#define LOG_LEVEL_CRITICAL 500
#define LOG_LEVEL_ALERT 550
#define LOG_LEVEL_EMERGENCY 600


#ifdef ARDUINO
#include <Arduino.h>

const __FlashStringHelper *get_level_name(int level) {
  switch (level) {
  case 100:
    return F("DEBUG");
  case 200:
    return F("INFO");
  case 250:
    return F("NOTICE");
  case 300:
    return F("WARNING");
  case 400:
    return F("ERROR");
  case 500:
    return F("CRITICAL");
  case 550:
    return F("ALERT");
  case 600:
    return F("EMERGENCY");
  }
  return F("TRACE");
}

#define LOGF(level, f_, ...)                                                   \
  {                                                                            \
    if (LOG_LEVEL <= level) {                                                  \
      Serial.print(F("["));                                                    \
      Serial.print(get_level_name(level));                                     \
      Serial.printf_P(PSTR("]::(%s:%d():"), __FILE__, __LINE__);                \
      Serial.printf_P(PSTR((f_)), __VA_ARGS__);                                \
      Serial.println();                                                        \
    }                                                                          \
  }
#define LOG(level, msg)                                                        \
  {                                                                            \
    if (LOG_LEVEL <= level) {                                                  \
      Serial.print(F("["));                                                    \
      Serial.print(get_level_name(level));                                     \
      Serial.printf_P(PSTR("]::(%s:%d):"), __FILE__, __LINE__);                \
      Serial.println(F(msg));                                                  \
    }                                                                          \
  }

#else

const char *get_level_name(int level) {
  switch (level) {
  case 100:
    return "DEBUG";
  case 200:
    return "INFO";
  case 250:
    return "NOTICE";
  case 300:
    return "WARNING";
  case 400:
    return "ERROR";
  case 500:
    return "CRITICAL";
  case 550:
    return "ALERT";
  case 600:
    return "EMERGENCY";
  }
  return "TRACE";
}

#define LOG(level, msg)                                                        \
  {                                                                            \
    if (LOG_LEVEL <= level) {                                                  \
      printf("[%s]", get_level_name(level));                                   \
      printf("::(%s:%d):", __FILE__, __LINE__);                                \
      printf("%s\n", msg);                                                     \
    }                                                                          \
  }

#define LOGF(level, f_, ...)                                                   \
  {                                                                            \
    if (LOG_LEVEL <= level) {                                                  \
      printf("[%s]", get_level_name(level));                                   \
      printf("::(%s:%d):", __FILE__, __LINE__);                                \
      printf(f_, __VA_ARGS__);                                                 \
      printf("\n");                                                            \
    }                                                                          \
  }
#endif

#if LOG_LEVEL <= LOG_LEVEL_TRACE
#define TRACE(msg)                                                             \
  { LOG(LOG_LEVEL_TRACE, msg); }
#define TRACEF(f_, ...)                                                        \
  { LOGF(LOG_LEVEL_TRACE, f_, __VA_ARGS__); }
#else
#define TRACE(msg)
#define TRACEF(f_, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define DEBUG(msg)                                                             \
  { LOG(LOG_LEVEL_DEBUG, msg); }
#define DEBUGF(f_, ...)                                                        \
  { LOGF(LOG_LEVEL_DEBUG, f_, __VA_ARGS__); }
#else
#define DEBUG(msg)
#define DEBUGF(f_, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define INFO(msg)                                                              \
  { LOG(LOG_LEVEL_INFO, msg); }
#define INFOF(f_, ...)                                                         \
  { LOGF(LOG_LEVEL_INFO, f_, __VA_ARGS__); }
#else
#define INFO(msg)
#define INFOF(f_, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_NOTICE
#define NOTICE(msg)                                                            \
  { LOG(LOG_LEVEL_NOTICE, msg); }
#define NOTICEF(f_, ...)                                                       \
  { LOGF(LOG_LEVEL_NOTICE, f_, __VA_ARGS__); }
#else
#define NOTICE(msg)
#define NOTICEF(f_, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARNING
#define WARNING(msg)                                                           \
  { LOG(LOG_LEVEL_WARNING, msg); }
#define WARNINGF(f_, ...)                                                      \
  { LOGF(LOG_LEVEL_WARNING, f_, __VA_ARGS__); }
#else
#define WARNING(msg)
#define WARNINGF(f_, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define ERROR(msg)                                                             \
  { LOG(LOG_LEVEL_ERROR, msg); }
#define ERRORF(f_, ...)                                                        \
  { LOGF(LOG_LEVEL_ERROR, f_, __VA_ARGS__); }
#else
#define ERROR(msg)
#define ERRORF(f_, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_CRITICAL
#define CRITICAL(msg)                                                          \
  { LOG(LOG_LEVEL_CRITICAL, msg); }
#define CRITICALF(f_, ...)                                                     \
  { LOGF(LOG_LEVEL_CRITICAL, f_, __VA_ARGS__); }
#else
#define CRITICAL(msg)
#define CRITICALF(f_, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ALERT
#define ALERT(msg)                                                             \
  { LOG(LOG_LEVEL_ALERT, msg); }
#define ALERTF(f_, ...)                                                        \
  { LOGF(LOG_LEVEL_ALERT, f_, __VA_ARGS__); }
#else
#define ALERT(msg)
#define ALERTF(f_, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_EMERGENCY
#define EMERGENCY(msg)                                                         \
  { LOG(LOG_LEVEL_EMERGENCY, msg); }
#define EMERGENCYF(f_, ...)                                                    \
  { LOGF(LOG_LEVEL_EMERGENCY, f_, __VA_ARGS__); }
#else
#define EMERGENCY(msg)
#define EMERGENCYF(f_, ...)
#endif

#endif      // #ifndef _KSLogger_H



