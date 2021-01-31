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

#include <jerry/builtin/messaging/echo/MessageHandler.h>
#include <jerry/Logger.h>

#include <esl/messaging/Producer.h>

#include <esl/Stacktrace.h>

#include <stdexcept>

#include <chrono>
#include <thread>
#include <memory>

namespace jerry {
namespace builtin {
namespace messaging {
namespace echo {

namespace {
Logger logger("jerry::builtin::messaging::echo::MessageHandler");
}

std::unique_ptr<esl::utility::Consumer> MessageHandler::create(esl::messaging::MessageContext& messageContext) {
	Settings* settings = dynamic_cast<Settings*>(messageContext.findObject(""));
	if(settings == nullptr) {
		return nullptr;
	}

	return std::unique_ptr<esl::utility::Consumer>(new MessageHandler(messageContext, *settings));
}

MessageHandler::MessageHandler(esl::messaging::MessageContext& aMessageContext, Settings& aSettings)
: messageContext(aMessageContext),
  settings(aSettings)
{ }

/* return: Reader::npos
 *           if there is no more data to read or Consumer is not interested for reading more data
 *
 *         Number of characters read from Reader */
std::size_t MessageHandler::read(esl::utility::Reader& reader)  {
	char data[1024];
	std::size_t len = reader.read(data, 1024);

	if(len == esl::utility::Reader::npos) {
		logger.info << "Echo - sleep " << settings.getMSDelay() << "ms\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(settings.getMSDelay()));

		std::unique_ptr<esl::messaging::Producer> producer = settings.createProducer();
		if(producer) {
			logger.info << "Echo - send echo\n";
			producer->send(message.data(), message.size());
		}
		else {
			logger.info << "Echo - send echo failed\n";
		}
	}
	else {
		message += std::string(data, len);
	}

	return len;
}

} /* namespace echo */
} /* namespace messaging */
} /* namespace builtin */
} /* namespace jerry */
