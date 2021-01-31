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

#include <jerry/config/Exceptions.h>

#include <esl/Stacktrace.h>

#include <stdexcept>

namespace jerry {
namespace config {

namespace {
std::string makeSpaces(std::size_t spaces) {
	std::string rv;
	for(std::size_t i=0; i<spaces; ++i) {
		rv += " ";
	}
	return rv;
}

bool stringToBool(bool& b, std::string str) {
	if(str == "true") {
		b = true;
	}
	else if(str == "false") {
		b = false;
	}
	else {
		return false;
	}
	return true;
}
}

Exceptions::Exceptions(const tinyxml2::XMLElement& element) {
	if(element.GetUserData() != nullptr) {
		throw esl::addStacktrace(std::runtime_error("Element has user data but it should be empty (line " + std::to_string(element.GetLineNum()) + ")"));
	}

	for(const tinyxml2::XMLAttribute* attribute = element.FirstAttribute(); attribute != nullptr; attribute = attribute->Next()) {
		if(std::string(attribute->Name()) == "inheritDocuments") {
			if(stringToBool(inheritDocuments, attribute->Value()) == false) {
				throw esl::addStacktrace(std::runtime_error(std::string("Unknown value \"") + attribute->Value() + "\" for attribute \"" + attribute->Name() + "\" at line " + std::to_string(element.GetLineNum())));
			}
		}
		else if(std::string(attribute->Name()) == "showExceptions") {
			bool b;
			if(stringToBool(b, attribute->Value()) == false) {
				throw esl::addStacktrace(std::runtime_error(std::string("Unknown value \"") + attribute->Value() + "\" for attribute \"" + attribute->Name() + "\" at line " + std::to_string(element.GetLineNum())));
			}
			showExceptions = b ? OptionalBool::obTrue : OptionalBool::obFalse;
		}
		else if(std::string(attribute->Name()) == "showStacktrace") {
			bool b;
			if(stringToBool(b, attribute->Value()) == false) {
				throw esl::addStacktrace(std::runtime_error(std::string("Unknown value \"") + attribute->Value() + "\" for attribute \"" + attribute->Name() + "\" at line " + std::to_string(element.GetLineNum())));
			}
			showStacktrace = b ? OptionalBool::obTrue : OptionalBool::obFalse;
		}
		else {
			throw esl::addStacktrace(std::runtime_error(std::string("Unknown attribute \"") + attribute->Name() + "\" at line " + std::to_string(element.GetLineNum())));
		}
	}

	for(const tinyxml2::XMLNode* node = element.FirstChild(); node != nullptr; node = node->NextSibling()) {
		const tinyxml2::XMLElement* innerElement = node->ToElement();

		if(innerElement == nullptr) {
			continue;
		}

		if(innerElement->Name() == nullptr) {
			throw esl::addStacktrace(std::runtime_error("Element name is empty at line " + std::to_string(innerElement->GetLineNum())));
		}

		std::string innerElementName(innerElement->Name());

		if(innerElementName == "document") {
			documents.push_back(ExceptionDocument(*innerElement));
		}
		else {
			throw esl::addStacktrace(std::runtime_error("Unknown element name \"" + std::string(innerElement->Name()) + "\" at line " + std::to_string(innerElement->GetLineNum())));
		}
	}
}

void Exceptions::save(std::ostream& oStream, std::size_t spaces) const {
	oStream << makeSpaces(spaces) << "<exceptions inheritDocuments=";

	if(inheritDocuments) {
		oStream << "\"true\"";
	}
	else {
		oStream << "\"false\"";
	}

	if(showExceptions == OptionalBool::obTrue) {
		oStream << " showExceptions=\"true\"";
	}
	else if(showExceptions == OptionalBool::obFalse) {
		oStream << " showExceptions=\"false\"";
	}

	if(showStacktrace == OptionalBool::obTrue) {
		oStream << " showStacktrace=\"true\"";
	}
	else if(showStacktrace == OptionalBool::obFalse) {
		oStream << " showStacktrace=\"false\"";
	}

	oStream << ">\n";

	for(const auto& entry : documents) {
		entry.save(oStream, spaces+2);
	}
	oStream << makeSpaces(spaces) << "<exceptions/>\n";

}

} /* namespace config */
} /* namespace jerry */
