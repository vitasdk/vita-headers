import ruamel.yaml as yaml

class HexWInt(yaml.scalarint.ScalarInt):
    def __new__(cls, value, width):
        x = yaml.scalarint.ScalarInt.__new__(cls, value)
        x._width = width   # keep the original width
        return x


def alt_construct_yaml_int(constructor, node):
    # check for 0x0 starting hex integers
    value_s = yaml.compat.to_str(constructor.construct_scalar(node))
    if not value_s.startswith('0x0'):
        return constructor.construct_yaml_int(node)
    return HexWInt(int(value_s[2:], 16), len(value_s[2:]))

yaml.constructor.RoundTripConstructor.add_constructor(
    u'tag:yaml.org,2002:int', alt_construct_yaml_int)

def represent_hexw_int(representer, data):
    return representer.represent_scalar(u'tag:yaml.org,2002:int',
                                        '0x{:0{}X}'.format(data, data._width))

yaml.representer.RoundTripRepresenter.add_representer(
HexWInt, represent_hexw_int)

f_db = open('db.yml')
db = yaml.round_trip_load(f_db)
f_db.close()

for module in db['modules']:
	module = db['modules'][module]
	for library in module['libraries']:
		library = module['libraries'][library]

		sorted_functions = yaml.comments.CommentedMap()
		for func in sorted(library['functions']):
		    sorted_functions[func] = library['functions'][func]

		library['functions'] = sorted_functions

f_db = open('db.yml', 'w')
yaml.dump(db, f_db, Dumper=yaml.RoundTripDumper, default_flow_style=False)
f_db.close()