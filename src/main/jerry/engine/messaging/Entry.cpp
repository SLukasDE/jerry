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

#include <jerry/engine/messaging/Entry.h>
#include <jerry/engine/messaging/Context.h>
#include <jerry/engine/messaging/Endpoint.h>

namespace jerry {
namespace engine {
namespace messaging {

Entry::Entry(std::unique_ptr<Context> aContext)
: context(std::move(aContext))
{ }

Entry::Entry(std::unique_ptr<Endpoint> aEndpoint)
: endpoint(std::move(aEndpoint))
{ }

Entry::Entry(esl::messaging::messagehandler::Interface::CreateMessageHandler aCreateMessageHandler)
: createMessageHandler(aCreateMessageHandler)
{ }

} /* namespace messaging */
} /* namespace engine */
} /* namespace jerry */
