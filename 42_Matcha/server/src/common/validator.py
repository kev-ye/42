_validator = {
	'name': lambda name: True if name is not None else False,
	'fname': lambda fname: True if fname is not None else False,
	'birthday': lambda bd: True if bd is not None else False,
	'sex': lambda sex: True if sex is not None else False,
	'sex_o': lambda sex_o: True if sex_o is not None else False,
	'tag_l': lambda tag: True if tag is not None else False,
	'username': lambda uname: True if uname is not None else False,
	'password': lambda psw: True if psw is not None else False,
	'email': lambda email: True if email is not None else False,
	'location': lambda location: True if location is not None else False,
	'bio': lambda bio: True if bio is not None else False
}


def data_validator(obj: dict):
	"""Data validator

	Return 'True' if all input value is correct otherwise return 'False'

	:param obj: key/value object
	"""
	if obj is None or type(obj) is not dict:
		return False

	for k, v in obj.items():
		if k not in _validator or v is None or _validator[k](v) is False:
			return False
	return True
