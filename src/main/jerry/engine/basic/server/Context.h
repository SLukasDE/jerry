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

#ifndef JERRY_ENGINE_BASIC_SERVER_CONTEXT_H_
#define JERRY_ENGINE_BASIC_SERVER_CONTEXT_H_

#include <jerry/engine/BaseContext.h>
#include <jerry/engine/basic/server/Entry.h>
#include <jerry/engine/basic/server/Writer.h>

#include <esl/object/Interface.h>
#include <esl/io/Input.h>

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <utility>


namespace jerry {
namespace engine {
namespace basic {
namespace server {

class Listener;

class Context : public BaseContext {
public:
	void addReference(const std::string& id, const std::string& refId);
	esl::object::Interface::Object& addObject(const std::string& id, const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) override;

	Context& addContext(bool inheritObjects);
	void addRequestHandler(const std::string& implementation);

	void initializeContext() override;
	void dumpTree(std::size_t depth) const override;
	std::set<std::string> getNotifier() const;

	/* lookup for object only in this context */
	virtual esl::object::Interface::Object* findLocalObject(const std::string& id) const;

	/* lookup for object up to it's parent context */
	virtual esl::object::Interface::Object* findHiddenObject(const std::string& id) const;

protected:
	Context(Listener& listener, const Context* parentContext, bool inheritObjects);

	esl::object::Interface::Object* findObject(const std::string& id) const override;

	esl::io::Input createRequestHandler(std::unique_ptr<server::Writer>& writer) const;

private:
	Listener& listener;
	const Context* parentContext = nullptr;

	/* If true:
	 *   findObject(...) calls findHiddenObject(...)
	 * If false:
	 *   findObject(...) calls findLocalObject(...)
	 */
	bool inheritObjects = true;

	std::map<std::string, esl::object::Interface::Object*> localObjectsById;

	std::vector<Entry> entries;
};

} /* namespace server */
} /* namespace basic */
} /* namespace engine */
} /* namespace jerry */

#endif /* JERRY_ENGINE_BASIC_SERVER_CONTEXT_H_ */
