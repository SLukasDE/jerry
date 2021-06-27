/*
 * This file is part of Jerry application server.
 * Copyright (C) 2020-2021 Sven Lukas
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

#include <jerry/Module.h>
#include <jerry/builtin/Properties.h>
#include <jerry/builtin/basic/dump/RequestHandler.h>
#include <jerry/builtin/basic/dump/Settings.h>
#include <jerry/builtin/basic/echo/RequestHandler.h>
#include <jerry/builtin/basic/echo/Settings.h>
#include <jerry/builtin/http/basicauth/RequestHandler.h>
#include <jerry/builtin/http/basicauth/Settings.h>
#include <jerry/builtin/http/filebrowser/RequestHandler.h>
#include <jerry/builtin/http/filebrowser/Settings.h>
#include <jerry/builtin/http/file/RequestHandler.h>
#include <jerry/builtin/http/file/Settings.h>
#include <jerry/builtin/http/self/RequestHandler.h>

#include <esl/com/basic/server/requesthandler/Interface.h>
#include <esl/com/http/server/requesthandler/Interface.h>
#include <esl/object/Interface.h>
#include <esl/module/Interface.h>

#include <memory>
#include <new>         // placement new
#include <type_traits> // aligned_storage

namespace jerry {

namespace {
class Module : public esl::module::Module {
public:
	Module();
};

typename std::aligned_storage<sizeof(Module), alignof(Module)>::type moduleBuffer; // memory for the object;
Module* modulePtr = nullptr;


Module::Module()
: esl::module::Module()
{
	esl::module::Module::initialize(*this);

	addInterface(esl::object::Interface::createInterface(
			jerry::builtin::Properties::getImplementation(),
			&jerry::builtin::Properties::createSettings));

/*
	addInterface(std::unique_ptr<const esl::module::Interface>(new esl::object::Interface(
			getId(), "jerry/builtin/messaging/producer-factory", &jerry::builtin::messaging::ProducerFactory::create)));
*/
	addInterface(esl::com::basic::server::requesthandler::Interface::createInterface(
			jerry::builtin::basic::dump::RequestHandler::getImplementation(),
			&jerry::builtin::basic::dump::RequestHandler::createInput,
			&jerry::builtin::basic::dump::RequestHandler::getNotifiers));
	addInterface(esl::object::Interface::createInterface(
			jerry::builtin::basic::dump::RequestHandler::getImplementation(),
			&jerry::builtin::basic::dump::RequestHandler::createSettings));

	addInterface(esl::com::basic::server::requesthandler::Interface::createInterface(
			jerry::builtin::basic::echo::RequestHandler::getImplementation(),
			&jerry::builtin::basic::echo::RequestHandler::createInput,
			&jerry::builtin::basic::echo::RequestHandler::getNotifiers));
	addInterface(esl::object::Interface::createInterface(
			jerry::builtin::basic::echo::RequestHandler::getImplementation(),
			&jerry::builtin::basic::echo::RequestHandler::createSettings));

	addInterface(esl::com::http::server::requesthandler::Interface::createInterface(
			jerry::builtin::http::basicauth::RequestHandler::getImplementation(),
			&jerry::builtin::http::basicauth::RequestHandler::createRequestHandler));
	addInterface(esl::object::Interface::createInterface(
			jerry::builtin::http::basicauth::RequestHandler::getImplementation(),
			&jerry::builtin::http::basicauth::RequestHandler::createSettings));

	addInterface(esl::com::http::server::requesthandler::Interface::createInterface(
			jerry::builtin::http::filebrowser::RequestHandler::getImplementation(),
			&jerry::builtin::http::filebrowser::RequestHandler::createRequestHandler));
	addInterface(esl::object::Interface::createInterface(
			jerry::builtin::http::filebrowser::RequestHandler::getImplementation(),
			&jerry::builtin::http::filebrowser::RequestHandler::createSettings));

	addInterface(esl::com::http::server::requesthandler::Interface::createInterface(
			jerry::builtin::http::file::RequestHandler::getImplementation(),
			&jerry::builtin::http::file::RequestHandler::createRequestHandler));
	addInterface(esl::object::Interface::createInterface(
			jerry::builtin::http::file::RequestHandler::getImplementation(),
			&jerry::builtin::http::file::RequestHandler::createSettings));

	addInterface(esl::com::http::server::requesthandler::Interface::createInterface(
			jerry::builtin::http::self::RequestHandler::getImplementation(),
			&jerry::builtin::http::self::RequestHandler::createRequestHandler));
}

} /* anonymous namespace */

esl::module::Module& getModule() {
	if(modulePtr == nullptr) {
		/* ***************** *
		 * initialize module *
		 * ***************** */

		modulePtr = reinterpret_cast<Module*> (&moduleBuffer);
		new (modulePtr) Module; // placement new
	}

	return *modulePtr;
}

} /* namespace jerry */
