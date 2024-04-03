from psycopg2.extras import RealDictCursor
from werkzeug.security import generate_password_hash

from db_init import get_db
from common.validator import data_validator


def insert_one(table_name: str, data: dict):
	"""Insert a row of data into the table

	Returns 'True' if the insertion was successful otherwise returns 'False'.

	:param table_name: name of table
	:param data: data object
	"""
	if type(table_name) is not str or data_validator(data) is False:
		return False

	columns, values = "", ""
	data_values = []
	idx = 0

	for k, v in data.items():
		columns += str(f'{k}, ' if idx != len(data) - 1 else f'{k}')
		values += str('%s, ' if idx != len(data) - 1 else '%s')
		data_values.append(generate_password_hash(v) if k == 'password' else v)
		idx += 1

	data_tuples = tuple(data_values)

	sql = f'INSERT INTO {table_name}({columns}) VALUES ({values})'

	print(sql)

	try:
		with get_db() as db, db.cursor() as cursor:
			cursor.execute(sql, data_tuples)
			# commit() call automatically in with block
			return True
	except (AttributeError, db.IntegrityError) as e:
		print('Exception:', e)
		return False


def find_one(table_name: str, key: str, value: any):
	"""find a data from table

	Returns data dict if data is found otherwise returns 'None'.

	:param table_name: name of table
	:param key: to find key
	:param value: to find value
	"""
	type_check = {
		"table_name": True if type(table_name) is str else False,
		"key": True if type(key) is str else False,
		"value": True if type(value) in [str, int] else False
	}
	for k, v in type_check.items():
		if v is False:
			return None

	sql = f'SELECT * FROM {table_name} WHERE {key} = %s'

	try:
		with get_db() as db, db.cursor(cursor_factory=RealDictCursor) as cursor:
			cursor.execute(sql, (value,))
			return cursor.fetchone()
	except (AttributeError, db.IntegrityError) as e:
		print('Exception:', e)
		return None


def update_one(table_name: str, data: dict, key: str, value: any):
	"""update a row of data from table

		Returns 'True' if the update was successful otherwise returns 'False'.

		:param table_name: name of table
		:param data: data object
		:param key: to find key
		:param value: to find value
		"""
	type_check = {
		"table_name": True if type(table_name) is str else False,
		"data": True if type(data) is dict and data_validator(data) else False,
		"key": True if type(key) is str else False,
		"value": True if type(value) in [str, int] else False
	}
	for k, v in type_check.items():
		if v is False:
			return False

	to_set = ""
	data_values = []
	idx = 0

	for k, v in data.items():
		to_set += str(f'{k} = %s, ' if idx != len(data) - 1 else f'{k} = %s')
		data_values.append(generate_password_hash(v) if k == 'password' else v)
		idx += 1
	data_values.append(value)

	data_tuples = tuple(data_values)

	sql = f'UPDATE {table_name} SET {to_set} WHERE {key} = %s'

	try:
		with get_db() as db, db.cursor() as cursor:
			cursor.execute(sql, data_tuples)
			# commit() call automatically in with block
			return True
	except (AttributeError, db.IntegrityError) as e:
		print('Exception:', e)
		return False
