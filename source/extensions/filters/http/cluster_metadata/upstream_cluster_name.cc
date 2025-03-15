// Copyright 2025 - David Protasowski

#include "source/extensions/filters/http/cluster_metadata/upstream_cluster_name.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace ClusterMetadata {

Http::FilterHeadersStatus
SetUpstreamClusterNameFilter::decodeHeaders(Http::RequestHeaderMap&, bool) {
    auto clusterName = decoder_callbacks_->clusterInfo()->name();
    auto val = MessageUtil::keyValueStruct("upstream_cluster_name", clusterName);
    decoder_callbacks_->streamInfo().setDynamicMetadata("dev.knit", val);
    return Http::FilterHeadersStatus::Continue;
}

absl::StatusOr<Http::FilterFactoryCb>
SetUpstreamClusterNameFilterFactory::createFilterFactoryFromProto(
    const Protobuf::Message&,
    const std::string&,
    Server::Configuration::FactoryContext&) {
  return [](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(std::make_shared<SetUpstreamClusterNameFilter>());
  };
}

REGISTER_FACTORY(
    SetUpstreamClusterNameFilterFactory,
    Server::Configuration::NamedHttpFilterConfigFactory
);

} // namespace ClusterMetadata
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
