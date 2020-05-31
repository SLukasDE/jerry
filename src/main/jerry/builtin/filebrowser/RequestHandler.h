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

#ifndef JERRY_BUILTIN_FILEBROWSER_REQUESTHANDLER_H_
#define JERRY_BUILTIN_FILEBROWSER_REQUESTHANDLER_H_

#include <jerry/builtin/filebrowser/Settings.h>

#include <esl/http/server/requesthandler/Interface.h>
#include <esl/http/server/RequestContext.h>
#include <esl/http/server/Request.h>

#include <string>

namespace jerry {
namespace builtin {
namespace filebrowser {

class RequestHandler : public esl::http::server::requesthandler::Interface::RequestHandler {
public:
	static std::unique_ptr<esl::http::server::requesthandler::Interface::RequestHandler> create(esl::http::server::RequestContext& requestContext);

	RequestHandler(esl::http::server::RequestContext& requestContext, const Settings& settings, bool isDirectory);

private:
	esl::http::server::RequestContext& requestContext;
	const Settings& settings;

	std::string outputContent;
	std::size_t outputPos = 0;

	int getData(char* buffer, std::size_t count);
};

} /* namespace filebrowser */
} /* namespace builtin */
} /* namespace jerry */

#endif /* JERRY_BUILTIN_FILEBROWSER_REQUESTHANDLER_H_ */