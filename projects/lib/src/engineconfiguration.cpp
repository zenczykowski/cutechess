/*
    This file is part of Cute Chess.

    Cute Chess is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Cute Chess is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Cute Chess.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "engineconfiguration.h"

EngineConfiguration::EngineConfiguration()
	: m_whiteEvalPov(false)
{

}

EngineConfiguration::EngineConfiguration(const QString& name,
                                         const QString& command,
					 const QString& protocol)
	: m_name(name),
	  m_command(command),
	  m_protocol(protocol),
	  m_whiteEvalPov(false)
{

}

EngineConfiguration::EngineConfiguration(const QVariant& variant)
	: m_whiteEvalPov(false)
{
	const QVariantMap map = variant.toMap();

	setName(map["name"].toString());
	setCommand(map["command"].toString());
	setWorkingDirectory(map["workingDirectory"].toString());
	setProtocol(map["protocol"].toString());

	if (map.contains("initStrings"))
		setInitStrings(map["initStrings"].toStringList());
	if (map.contains("whitepov"))
		setWhiteEvalPov(map["whitepov"].toBool());
}

QVariant EngineConfiguration::toVariant() const
{
	QVariantMap map;

	map.insert("name", m_name);
	map.insert("command", m_command);
	map.insert("workingDirectory", m_workingDirectory);
	map.insert("protocol", m_protocol);

	// Convert QStringList objects to QVariantList because the latest "stable"
	// release of QJson (v0.7.1) doesn't serialize QStringLists.
	if (!m_initStrings.isEmpty())
		map.insert("initStrings", QVariant(m_initStrings).toList());
	if (m_whiteEvalPov)
		map.insert("whitepov", true);

	return map;
}

void EngineConfiguration::setName(const QString& name)
{
	m_name = name;
}

void EngineConfiguration::setCommand(const QString& command)
{
	m_command = command;
}

void EngineConfiguration::setProtocol(const QString& protocol)
{
	m_protocol = protocol;
}

void EngineConfiguration::setWorkingDirectory(const QString& workingDir)
{
	m_workingDirectory = workingDir;
}

QString EngineConfiguration::name() const
{
	return m_name;
}

QString EngineConfiguration::command() const
{
	return m_command;
}

QString EngineConfiguration::workingDirectory() const
{
	return m_workingDirectory;
}

QString EngineConfiguration::protocol() const
{
	return m_protocol;
}

QStringList EngineConfiguration::arguments() const
{
	return m_arguments;
}

void EngineConfiguration::setArguments(const QStringList& arguments)
{
	m_arguments = arguments;
}

void EngineConfiguration::addArgument(const QString& argument)
{
	m_arguments << argument;
}

QStringList EngineConfiguration::initStrings() const
{
	return m_initStrings;
}

void EngineConfiguration::setInitStrings(const QStringList& initStrings)
{
	m_initStrings = initStrings;
}

void EngineConfiguration::addInitString(const QString& initString)
{
	m_initStrings << initString;
}

QMap<QString, QVariant> EngineConfiguration::customOptions() const
{
	return m_customOptions;
}

void EngineConfiguration::setCustomOptions(const QMap<QString, QVariant>& customOptions)
{
	m_customOptions = customOptions;
}

void EngineConfiguration::addCustomOption(const QString& name, const QVariant& value)
{
	m_customOptions[name] = value;
}

bool EngineConfiguration::whiteEvalPov() const
{
	return m_whiteEvalPov;
}

void EngineConfiguration::setWhiteEvalPov(bool whiteEvalPov)
{
	m_whiteEvalPov = whiteEvalPov;
}
