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

#ifndef JERRY_ENGINE_MESSAGING_MESSAGE_H_
#define JERRY_ENGINE_MESSAGING_MESSAGE_H_

#include <esl/messaging/Message.h>
#include <esl/utility/Reader.h>
#include <esl/utility/ReaderBuffered.h>

#include <string>

namespace jerry {
namespace engine {
namespace messaging {

class Message : public esl::messaging::Message {
public:
	Message(esl::messaging::Message& baseMessage);

	std::string getValue(const std::string& key) const override;

	esl::utility::ReaderBuffered& getReaderBuffered();
	esl::utility::Reader& getReader() override;

private:
	esl::messaging::Message& baseMessage;
	esl::utility::ReaderBuffered readerBuffered;
};

} /* namespace messaging */
} /* namespace engine */
} /* namespace jerry */

#endif /* JERRY_ENGINE_MESSAGING_MESSAGE_H_ */
