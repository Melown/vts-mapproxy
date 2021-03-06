/**
 * Copyright (c) 2019 Melown Technologies SE
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * *  Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef mapproxy_gdalsupport_workrequest_hpp_included_
#define mapproxy_gdalsupport_workrequest_hpp_included_

#include "types.hpp"
#include "datasetcache.hpp"
#include "workrequestfwd.hpp"

// forward declaration for custom sh request
class WorkRequest : boost::noncopyable {
public:
    WorkRequest(ManagedBuffer &sm) : sm_(sm) {}

    virtual ~WorkRequest();
    virtual void process(bi::interprocess_mutex &mutex, DatasetCache &cache)
    = 0;

    using Response = WorkResponse;

    virtual Response response(Lock &lock) = 0;

    /** Destroys this instance. Needed because ManagedBuffer::destroy_ptr()
     *  doesn't cope with polymorphism.
     *
     *  Should call sm().destroy_ptr(this), nothing else!
     */
    virtual void destroy() = 0;

    ManagedBuffer& sm() { return sm_; };

private:
    ManagedBuffer &sm_;
};

struct WorkRequestParams {
    ManagedBuffer &sm;
    WorkRequestParams(ManagedBuffer &sm) : sm(sm) {}
};

#endif // mapproxy_gdalsupport_workrequest_hpp_included_
