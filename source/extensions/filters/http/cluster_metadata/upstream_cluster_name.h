// Copyright 2025 - David Protasowski

#pragma once

#include "envoy/server/filter_config.h"
#include "source/extensions/filters/http/cluster_metadata/config.pb.h"
#include "source/extensions/filters/http/common/factory_base.h"
#include "source/extensions/filters/http/common/pass_through_filter.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace ClusterMetadata {

class SetUpstreamClusterNameFilterFactory : public Server::Configuration::NamedHttpFilterConfigFactory {
public:
  std::string name() const override { return "envoy.filters.http.cluster_meta.setup_upstream_name"; }

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return std::make_unique<clustermeta::Config>();
  }

  absl::StatusOr<Http::FilterFactoryCb>
  createFilterFactoryFromProto(
    const Protobuf::Message& config,
    const std::string& stat_prefix,
    Server::Configuration::FactoryContext& context) override;
};

class SetUpstreamClusterNameFilter :
  public Http::PassThroughDecoderFilter,
  public Logger::Loggable<Logger::Id::filter> {

public:
  // Http::StreamFilterBase
  void onDestroy() override {}

  Http::FilterHeadersStatus decodeHeaders(Http::RequestHeaderMap& headers, bool) override;
  void setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks) override {
    decoder_callbacks_ = &callbacks;
  }

private:
  Http::StreamDecoderFilterCallbacks* decoder_callbacks_;
};

} // namespace ClusterMetadata
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
