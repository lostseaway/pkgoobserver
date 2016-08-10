{
    "targets": [
        {
            "target_name": "NativeExtension",
            "sources": [
                "src/NativeExtension.cc",
                "src/point.cc",
                "src/latlng.cc",
                "src/cellid.cc",
                "src/cell.cc",
                "src/latlngrect.cc",
                "src/cap.cc",
                "src/interval.cc",
                "src/angle.cc",
                "./geometry/s2.cc",
                "./geometry/s1interval.cc",
                "./geometry/util/math/exactfloat/exactfloat.cc",
                "./geometry/base/logging.cc",
                "./geometry/strings/split.cc",
                "./geometry/strings/strutil.cc",
                "./geometry/strings/strtoint.cc",
                "./geometry/strings/stringprintf.cc",
          	    "./geometry/s2cap.cc",
          	    "./geometry/s1angle.cc",
          	    "./geometry/s2cell.cc",
          	    "./geometry/s2cellunion.cc",
          	    "./geometry/s2cellid.cc",
          	    "./geometry/s2edgeindex.cc",
          	    "./geometry/s2edgeutil.cc",
          	    "./geometry/s2latlngrect.cc",
          	    "./geometry/s2loop.cc",
          	    "./geometry/s2pointregion.cc",
          	    "./geometry/s2latlng.cc",
          	    "./geometry/s2polygon.cc",
          	    "./geometry/s2polygonbuilder.cc",
          	    "./geometry/s2polyline.cc",
          	    "./geometry/s2r2rect.cc",
          	    "./geometry/s2region.cc",
          	    "./geometry/s2regioncoverer.cc",
          	    "./viewfinder/viewfinder.cc"
            ],
            "defines": [
                'NDEBUG',
                'GNU_C',
                '_GNU_SOURCE'
            ],
            "include_dirs": [
                "./viewfinder/",
                "./geometry/",
                "./geometry/base/",
                "./geometry/util/",
                "./geometry/util/math/",
                "./geometry/strings/"
            ],
            'conditions': [
                ['OS=="mac"', {
                    'xcode_settings': {
                        'OTHER_CPLUSPLUSFLAGS':[
                            '-Wno-deprecated',
                            '-Wno-ignored-qualifiers',
                            '-Wno-absolute-value',
                            '-Wno-unused-result',
                            '-Wno-dynamic-class-memaccess',
                            '-DARCH_K8 -DS2_USE_EXACTFLOAT',
                            '-stdlib=libc++',
                            '-std=c++11'
                        ],
                        'OTHER_LDFLAGS':[
                            '-flat_namespace -undefined suppress',
                            '-stdlib=libc++',
                            '-std=c++11'
                        ],
                        'GCC_ENABLE_CPP_RTTI': 'YES',
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                        'MACOSX_DEPLOYMENT_TARGET': '10.7',
                    }
                }],
                ['OS=="linux"', {
                    'cflags_cc' : [
                    '-Wno-deprecated',
                    '-Wno-ignored-qualifiers',
                    '-DARCH_K8 -DS2_USE_EXACTFLOAT',
                    '-std=c++11'
                    ],
                }],
                ['OS=="win"', {
                    'conditions': [
                      [
                        'target_arch=="x64"', {
                          'variables': {
                            'openssl_root%': '../openssl/x64'
                          },
                        }, {
                           'variables': {
                             'openssl_root%': '../openssl/x86'
                            }
                        }
                      ]
                    ],
                    'libraries': [ 
                      '-l<(openssl_root)/lib/libeay32.lib',
                    ],
                    'include_dirs': [
                      '<(openssl_root)/include',
                    ],
                }]
            ]
        }
    ]
}