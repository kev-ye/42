import { ObjectId } from "mongodb";

export interface Comment {
	user: string,
	comment: string,
	date: Date
}

export interface Social {
	like: string[],
	comment: Comment[]
}

export interface IFile {
	data: string,
	date: Date,
	user: string,
	id: string,
	social: Social
}

export class File {
	constructor (
		public path: string,
		public user: string,
		public _social?: Social,
		public _date?: Date,
		public _id?: ObjectId 
	) {}
}