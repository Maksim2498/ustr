cmake_minimum_required(VERSION 3.12)

project(ustr
        VERSION     0.1.0
        LANGUAGES   C
        DESCRIPTION "Small C library for unicode strings handling"
        HOMEPAGE_URL https://github.com/Maksim2498/ustr)


include(scripts/cache.cmake)
include(scripts/config.cmake)
include(scripts/add-target.cmake)
include(scripts/install.cmake)