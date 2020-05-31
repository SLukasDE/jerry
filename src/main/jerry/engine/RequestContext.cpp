/*
 * This file is part of Jerry application server.
 * Copyright (C) 2020 Sven Lukas
 *
 * Jerry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Jerry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with Jerry.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <jerry/engine/RequestContext.h>
#include <jerry/engine/Context.h>

namespace jerry {
namespace engine {

RequestContext::RequestContext(esl::http::server::RequestContext& aBaseRequestContext, const Context& aEngineContext)
: esl::http::server::RequestContext(),
  baseRequestContext(aBaseRequestContext),
  connection(*this, baseRequestContext.getConnection()),
  engineContext(std::cref(aEngineContext))
{
}

void RequestContext::setPath(std::string aPath) {
	path = std::move(aPath);
}

void RequestContext::setEngineContext(const Context& aEngineContext) {
	  engineContext = std::ref(aEngineContext);
}

const Context& RequestContext::getEngineContext() const {
	return engineContext.get();
}

esl::http::server::Connection& RequestContext::getConnection() const {
	return connection;
}

const esl::http::server::Request& RequestContext::getRequest() const {
	return baseRequestContext.getRequest();
}

const std::string& RequestContext::getPath() const {
	return path;
}

esl::object::Interface::Object* RequestContext::getObject(const std::string& id) const {
	esl::object::Interface::Object* object = engineContext.get().getObject(id);
	if(object == nullptr) {
		object = baseRequestContext.getObject(id);
	}
	return object;
}

} /* namespace engine */
} /* namespace jerry */