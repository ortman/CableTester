#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "MainCable.hpp"

#define CMD_EOF					"#EOF"
#define CMD_COMMENT			"##"
#define CMD_LEFT				"#LEFT"
#define CMD_RIGHT				"#RIGHT"
#define CMD_CABLE				"#CABLE"
#define CMD_CONNECTIONS	"#CONNECTIONS"

class Parser {
private:
	static String _line;
	static int _level;
	
	static void nextLine() {
		if (!_line.IsEqual(CMD_EOF))	_line.Clear();
	}
	
	static String getLine(FileIn &f) {
		if (!_line.IsEmpty()) {
			return _line;
		}
		int i;
		while (!f.IsEof()) {
			_line = f.GetLine();
			i = _line.Find(CMD_COMMENT);
			if (i >= 0) {
				_line = _line.Left(i);
			}
			for (i = 0; i < _line.GetCount(); ++i) {
				if (_line[i] != 32 && _line[i] != 9) break;
			}
			if (i < _line.GetCount()) {
				if (i > 0) {
					_line = _line.Mid(i);
				}
				_level = i;
				return _line;
			}
		}
		_line = CMD_EOF;
		return CMD_EOF;
	}
	
	static bool parseLeftRight(FileIn &f, MainCable &cable, bool isLeft) {
		nextLine();
		String line;
		int id = 0;
		int pinCount = 0;
		String name;
		const char *str;
		bool overflow = false;
		Connector *c;
		while (!(line = getLine(f)).IsEqual(CMD_EOF)) {
			if (_level > 1) return false;
			str = ScanInt<char, byte, uint32, int, 10>(id, line.Begin(), overflow);
			if (str == 0 || overflow) break;
			if (*str != '(') break;
			str = ScanInt<char, byte, uint32, int, 10>(pinCount, str+1, overflow);
			if (str == 0 || overflow) break;
			if (*str != ')') break;
			name = String(str+1);
			name.Replace("\\n", "\n");
			c = new Connector(name, pinCount, isLeft);
			ViewerSelector::Add(c);
			cable.AddConnector(id, c);
			nextLine();
		}
		return true;
	}
	
	static bool parseCmdConnections(FileIn &f, Cable &cable, Connector *cLeft, Connector *cRight, int level) {
		if (cLeft != NULL && cRight != NULL && cLeft->IsLeft() == cRight->IsLeft()) return false;
		const char *str;
		String line;
		bool overflow = false;
		int pinLeft, pinRight, color;
		Wire *wire;
		while (!(line = getLine(f)).IsEqual(CMD_EOF)) {
			if (_level < level) {
				return true;
			}
			if (line[0] == '-') {
				if (cLeft != NULL) return false;
				str = line.Begin() + 1;
				pinLeft = 0;
			} else {
				str = ScanInt<char, byte, uint32, int, 10>(pinLeft, line.Begin(), overflow);
				if (str == 0 || overflow) return false;
			}
			if (*str != '-' || str[1] == 0) return false;
			if (str[1] == '-') {
				if (cRight != NULL) return false;
				str+=2;
				pinRight = 0;
			} else {
				str = ScanInt<char, byte, uint32, int, 10>(pinRight, str+1, overflow);
				if (str == 0 || overflow) return false;
			}
			if (*str != '#') return false;
			str = ScanInt<char, byte, uint32, int, 16>(color, str+1, overflow);
			if (str == 0 || overflow) return false;
			if ((cLeft != NULL && cLeft->IsRight()) || (cRight != NULL && cRight->IsLeft())) {
				wire = new Wire(color, cRight, pinRight, cLeft, pinLeft);
			} else {
				wire = new Wire(color, cLeft, pinLeft, cRight, pinRight);
			}
			ViewerSelector::Add(wire);
			cable.Add(wire);
			nextLine();
		}
		return true;
	}
	
	static bool parseCable(FileIn &f, MainCable &mc, Cable &cable, int level) {
		String line;
		String name;
		bool result = true;
		const char *str;
		int idLeft, idRight;
		bool overflow = false;
		while (result && !(line = getLine(f)).IsEqual(CMD_EOF) && _level >= level) {
			if (line.StartsWith(CMD_CABLE)) {
				int startName = 6;
				Color color = CableNode::DarkColor(cable.GetColor(), 0.8);
				if (line[startName] == '#') {
					int hexColor;
					str = ScanInt<char, byte, uint32, int, 16>(hexColor, line.Begin() + startName + 1, overflow);
					if (str == 0 || overflow) {
						result = false;
						break;
					};
					color = Color::Special((hexColor & 0x0000ff) << 16 | (hexColor & 0x00ff00) | (hexColor & 0xff0000) >> 16);
					startName += 7;
				}
				name = line.Mid(startName + 1);
				Cable *c = new Cable(name, color);
				ViewerSelector::Add(c);
				cable.Add(c);
				nextLine();
				result = parseCable(f, mc, *c, _level+1);
			} else if (line.StartsWith(CMD_CONNECTIONS)) {
				if (line[13] == '-') {
					idLeft = 0;
					str = line.Begin() + 14;
				} else {
					str = line.Begin() + 13;
					str = ScanInt<char, byte, uint32, int, 10>(idLeft, str, overflow);
					if (str == 0 || overflow) {
						result = false;
						break;
					};
				}
				if (*str != '-') {
					result = false;
					break;
				}
				if (str[1] == '-') {
					idRight = 0;
				} else {
					str = ScanInt<char, byte, uint32, int, 10>(idRight, str + 1, overflow);
					if (str == 0 || overflow) {
						result = false;
						break;
					};
				}
				nextLine();
				result = parseCmdConnections(f, cable, mc.GetConnector(idLeft), mc.GetConnector(idRight), _level + 1);
			} else {
				RLOG("Unknown command: " << line);
				nextLine();
			}
		}
		return result;
	}
	
public:
	static MainCable* LoadFromFile(String fileName, String name = "") {
		_line = "";
		_level = 0;
		if (name.IsEmpty()) {
			name = GetFileName(fileName);
			name.TrimLast(4);
		}
		MainCable* cable = new MainCable(name);
		cable->ClearConnectors();
		
		FileIn  f(fileName);
		String cmd;
		bool result = true;
		while (result && !(cmd = getLine(f)).IsEqual(CMD_EOF)) {
			if (_level != 0) {
				result = false;
				break;
			}
			if (cmd.StartsWith(CMD_LEFT)) {
				result = parseLeftRight(f, *cable, true);
			} else if (cmd.StartsWith(CMD_RIGHT)) {
				result = parseLeftRight(f, *cable, false);
			} else {
				Cable* c = new Cable(name, White);
				result = parseCable(f, *cable, *c, _level);
				cable->SetCable(c);
			}
		}
		if (!result) RLOG("parse error! line:" << getLine(f));
		f.Close();
		
		return cable;
	}
};

String Parser::_line = "";
int Parser::_level = 0;

#endif
