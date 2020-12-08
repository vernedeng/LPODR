## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
    module = bld.create_ns3_module('lpodr', ['location-service','internet', 'wifi'])
    module.includes = '.'
    module.source = [
        'model/lpodr-id-cache.cc',
        'model/lpodr-dpd.cc',
        'model/lpodr-rtable.cc',
        'model/lpodr-rqueue.cc',
        'model/lpodr-packet.cc',
        'model/lpodr-neighbor.cc',
        'model/lpodr-routing-protocol.cc',
        'helper/lpodr-helper.cc',
        'model/van-convert.cc'
        ]

 

    headers = bld(features='ns3header')
    headers.module = 'lpodr'
    headers.source = [
        'model/lpodr-id-cache.h',
        'model/lpodr-dpd.h',
        'model/lpodr-rtable.h',
        'model/lpodr-rqueue.h',
        'model/lpodr-packet.h',
        'model/lpodr-neighbor.h',
        'model/lpodr-routing-protocol.h',
        'helper/lpodr-helper.h',
        'model/van-convert.h'
        ]

    if bld.env['ENABLE_EXAMPLES']:
        bld.recurse('examples')

    bld.ns3_python_bindings()
