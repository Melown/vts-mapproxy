#ifndef mapproxy_generator_tms_factory_hpp_included_
#define mapproxy_generator_tms_factory_hpp_included_

#include "../generator.hpp"

namespace generator {

class TmsRaster : public Generator {
public:
    TmsRaster(const Config &config, const Resource &resource);

private:
    virtual void prepare_impl();
    virtual vts::MapConfig
    mapConfig_impl(ResourceRoot root) const;

    virtual Task generateFile_impl(const FileInfo &fileInfo
                                   , const Sink::pointer &sink) const;

    const resdef::TmsRaster &definition_;
};

} // namespace generator

#endif // mapproxy_generator_tms_factory_hpp_included_
