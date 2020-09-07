/**
 * Copyright (c) 2018 Melown Technologies SE
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

#include <map>

#include "../error.hpp"
#include "factory.hpp"

namespace resource {

namespace {
typedef std::map<Resource::Generator
                 , std::function<DefinitionBase::pointer()>> Registry;

Registry& registry() {
    static Registry registry;
    return registry;
}

} // namespace

DefinitionBase::pointer definition(const Resource::Generator &type)
{
    const auto &r(registry());
    auto fregistry(r.find(type));
    if (fregistry == r.end()) {
        for (const auto &item : registry()) {
            LOG(info4) << "    " << item.first;
        }
        LOGTHROW(err1, UnknownGenerator)
            << "Unknown generator type <" << type << ">.";
    }
    return fregistry->second();
}

void registerDefinition(const Resource::Generator &type
                        , const std::function<DefinitionBase::pointer()>
                        &factory)
{
    LOG(info4) << "registering <" << type << ">.";
    registry().insert(Registry::value_type(type, factory));
}

} // namespace resource
