/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_HPP
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/preprocessor/cat.hpp>

// Ignores any data after the sequence if such data exists
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ( variadic_seq )                        \
BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_AFTER_RESCAN                                \
( BOOST_PP_CAT( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_                               \
              , BOOST_GENERIC_DETAIL_SEQ_SIZE( variadic_seq )                  \
              ) variadic_seq                                                   \
)

#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_1( ... )                               \
((__VA_ARGS__)),
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_2( ... )                               \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_1
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_3( ... )                               \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_2
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_4( ... )                               \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_3
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_5( ... )                               \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_4
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_6( ... )                               \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_5
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_7( ... )                               \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_6
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_8( ... )                               \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_7
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_9( ... )                               \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_8
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_10( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_9
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_11( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_10
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_12( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_11
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_13( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_12
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_14( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_13
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_15( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_14
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_16( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_15
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_17( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_16
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_18( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_17
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_19( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_18
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_20( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_19
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_21( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_20
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_22( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_21
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_23( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_22
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_24( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_23
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_25( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_24
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_26( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_25
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_27( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_26
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_28( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_27
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_29( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_28
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_30( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_29
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_31( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_30
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_32( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_31
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_33( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_32
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_34( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_33
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_35( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_34
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_36( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_35
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_37( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_36
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_38( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_37
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_39( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_38
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_40( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_39
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_41( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_40
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_42( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_41
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_43( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_42
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_44( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_43
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_45( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_44
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_46( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_45
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_47( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_46
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_48( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_47
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_49( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_48
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_50( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_49
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_51( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_50
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_52( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_51
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_53( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_52
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_54( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_53
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_55( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_54
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_56( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_55
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_57( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_56
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_58( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_57
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_59( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_58
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_60( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_59
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_61( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_60
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_62( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_61
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_63( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_62
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_64( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_63
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_65( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_64
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_66( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_65
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_67( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_66
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_68( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_67
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_69( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_68
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_70( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_69
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_71( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_70
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_72( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_71
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_73( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_72
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_74( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_73
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_75( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_74
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_76( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_75
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_77( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_76
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_78( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_77
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_79( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_78
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_80( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_79
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_81( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_80
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_82( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_81
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_83( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_82
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_84( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_83
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_85( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_84
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_86( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_85
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_87( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_86
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_88( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_87
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_89( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_88
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_90( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_89
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_91( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_90
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_92( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_91
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_93( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_92
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_94( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_93
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_95( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_94
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_96( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_95
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_97( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_96
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_98( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_97
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_99( ... )                              \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_98
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_100( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_99
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_101( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_100
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_102( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_101
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_103( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_102
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_104( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_103
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_105( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_104
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_106( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_105
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_107( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_106
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_108( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_107
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_109( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_108
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_110( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_109
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_111( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_110
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_112( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_111
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_113( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_112
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_114( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_113
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_115( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_114
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_116( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_115
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_117( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_116
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_118( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_117
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_119( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_118
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_120( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_119
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_121( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_120
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_122( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_121
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_123( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_122
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_124( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_123
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_125( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_124
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_126( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_125
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_127( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_126
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_128( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_127
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_129( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_128
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_130( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_129
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_131( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_130
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_132( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_131
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_133( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_132
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_134( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_133
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_135( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_134
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_136( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_135
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_137( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_136
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_138( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_137
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_139( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_138
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_140( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_139
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_141( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_140
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_142( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_141
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_143( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_142
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_144( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_143
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_145( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_144
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_146( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_145
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_147( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_146
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_148( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_147
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_149( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_148
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_150( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_149
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_151( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_150
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_152( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_151
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_153( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_152
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_154( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_153
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_155( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_154
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_156( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_155
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_157( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_156
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_158( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_157
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_159( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_158
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_160( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_159
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_161( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_160
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_162( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_161
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_163( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_162
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_164( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_163
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_165( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_164
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_166( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_165
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_167( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_166
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_168( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_167
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_169( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_168
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_170( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_169
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_171( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_170
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_172( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_171
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_173( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_172
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_174( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_173
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_175( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_174
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_176( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_175
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_177( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_176
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_178( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_177
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_179( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_178
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_180( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_179
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_181( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_180
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_182( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_181
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_183( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_182
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_184( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_183
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_185( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_184
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_186( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_185
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_187( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_186
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_188( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_187
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_189( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_188
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_190( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_189
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_191( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_190
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_192( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_191
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_193( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_192
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_194( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_193
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_195( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_194
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_196( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_195
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_197( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_196
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_198( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_197
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_199( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_198
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_200( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_199
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_201( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_200
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_202( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_201
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_203( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_202
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_204( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_203
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_205( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_204
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_206( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_205
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_207( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_206
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_208( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_207
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_209( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_208
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_210( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_209
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_211( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_210
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_212( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_211
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_213( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_212
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_214( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_213
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_215( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_214
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_216( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_215
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_217( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_216
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_218( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_217
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_219( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_218
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_220( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_219
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_221( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_220
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_222( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_221
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_223( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_222
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_224( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_223
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_225( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_224
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_226( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_225
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_227( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_226
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_228( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_227
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_229( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_228
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_230( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_229
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_231( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_230
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_232( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_231
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_233( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_232
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_234( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_233
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_235( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_234
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_236( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_235
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_237( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_236
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_238( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_237
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_239( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_238
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_240( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_239
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_241( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_240
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_242( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_241
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_243( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_242
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_244( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_243
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_245( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_244
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_246( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_245
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_247( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_246
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_248( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_247
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_249( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_248
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_250( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_249
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_251( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_250
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_252( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_251
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_253( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_252
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_254( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_253
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_255( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_254
#define BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_256( ... )                             \
((__VA_ARGS__)) BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_255


#endif // BOOST_GENERIC_DETAIL_SEQ_TO_SEQ_HPP
