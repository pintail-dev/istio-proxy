load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
)

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

envoy_cc_library(
    name = "upstream_cluster_name",
    srcs = ["upstream_cluster_name.cc"],
    hdrs = ["upstream_cluster_name.h"],
    repository = "@envoy",
    deps = [
        ":config_cc_proto",
        "@envoy//envoy/registry",
        "@envoy//source/common/http:utility_lib",
        "@envoy//source/common/protobuf:utility_lib",
        "@envoy//source/extensions/filters/http/common:factory_base_lib",
        "@envoy//source/extensions/filters/http/common:pass_through_filter_lib",
    ],
)

cc_proto_library(
    name = "config_cc_proto",
    deps = ["config"],
)

proto_library(
    name = "config",
    srcs = ["config.proto"],
)
