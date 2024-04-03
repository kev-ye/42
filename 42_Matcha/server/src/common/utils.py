from flask import make_response


def msg_response(msg: str, code: int):
	return make_response({"msg": msg}, code)
