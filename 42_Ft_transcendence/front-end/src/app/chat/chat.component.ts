import { HttpClient } from '@angular/common/http';
import { AfterViewChecked, Component, ElementRef, EventEmitter, Input, OnDestroy, OnInit, Output, ViewChild } from '@angular/core';
import { MatDialog } from '@angular/material/dialog';
import { io, Socket } from 'socket.io-client';
import { DialogInvite } from './dialogs/dialog-invite-channel.component';
import { DialogChannelSettings } from './dialogs/dialog-channel-settings.component';
import { DialogCreateChat } from './dialogs/dialog-create-chat.component';
import { DialogProtectedChat } from './dialogs/dialog-protected-chat.component';
import { DialogSpectator } from './dialogs/dialog-spectator.component';
import { DialogUser } from './dialogs/dialog-user.component';
import { DialogAddFriend } from './dialogs/dialog-add-friend.component';
import { DialogMuted } from './dialogs/dialog-muted.component';
import { GlobalConsts } from '../common/global';
import {DataSharedService} from "../service/data/data-shared.service";
import {Subscription} from "rxjs";

export const MAX_MESSAGE = 50;

@Component({
	selector: 'app-chat',
	templateUrl: './chat.component.html',
	styleUrls: ['./chat.component.css']
})
export class ChatComponent implements OnInit, OnDestroy, AfterViewChecked {
	constructor(
		public dialog: MatDialog,
		private http: HttpClient,
		private data: DataSharedService) { }

	isLogin: boolean = false;

	private subscription: Subscription = new Subscription();

	chat: {
		show: boolean,
		public: boolean,
		access: number,
		id: string,
		user_id: string,
		name: string,
		moderator: boolean,
		creator_id: string,
	} = {
		show: false,
		public: true,
		name: "",
		id: "",
		user_id: "",
		moderator: true,
		creator_id: '79139',
		access: 0
	};

	messages: {
		id: string,
		username?: string,
		user_id: string,
		type: number,
		message?: string
	}[] = [];

	scroll: boolean = false;
	friendList: any[] = [];
	focus: string = "";
	channelList: any[] = [];
	colorMap: Map<string, string> = new Map<string, string>();
	socket: Socket;
	blocked: any[] = [];

	fetchSub: any | null = null;

	myGame: any = null;

	user: any = {}
	password: string = "";

	@ViewChild('input') input: ElementRef<HTMLInputElement>;

	@ViewChild('inputPrivate') inputPrivate: ElementRef<HTMLInputElement>;

	@ViewChild('framePublic') framePublic: ElementRef<HTMLDivElement>;
	@ViewChild('framePrivate') framePrivate: ElementRef<HTMLDivElement>;

	@Output() join = new EventEmitter<string>();

	ngAfterViewChecked(): void {
		if (this.scroll && this.chat.id) {			
			if (this.chat.public && this.framePublic)
				this.framePublic.nativeElement.scroll({ top: this.framePublic.nativeElement.scrollHeight, behavior: "smooth" });
			else if (!this.chat.public && this.framePrivate)
				this.framePrivate.nativeElement.scroll({ top: this.framePrivate.nativeElement.scrollHeight, behavior: "smooth" });
			this.scroll = false;
		}
	}

	async sleep(ms: number) {
		return new Promise((r) => setTimeout(r, ms));
	  }

	fetchChannels() {
		return this.http.get(`${GlobalConsts.userApi}/channels/`, {
			withCredentials: true
		}).subscribe({
			next: data => {
				this.channelList = data as any[];
				
			},
			error: _ => {
			}});
	}

	deleteFriend(friend: any) {
		this.http.patch(`${GlobalConsts.userApi}/friend`,
		{
			first: this.user.id,
			second: friend.id
		}, {withCredentials: true}).subscribe({
			next: data => {
				this.fetchFriends();

			}, error: data => {
			}
		});
	}

	openFriendDialog() {
		const tmp = this.dialog.open(DialogAddFriend, {
			data: {
				my_id: this.user.id
			}
		});
		tmp.afterClosed().subscribe(() => {
			this.fetchFriends();
		})
	}

	openChannelSettings() {
		if (!this.user || !this.chat || this.chat.creator_id != this.user.id)
			return;
		const tmp = this.dialog.open(DialogChannelSettings, {
			data: {
				...this.chat,
				user_id: this.user.id, //data
			}
		});
		tmp.afterClosed().subscribe(() => {
			this.fetchChannels();
		})
	}

	fetchPrivateMessage(friend: any) {
		this.messages = [];
		this.http.get(`${GlobalConsts.userApi}/private/` + this.user.id + "/" + friend.id, { withCredentials: true }).subscribe(data => {
			this.messages = data as { id: string, username: string, user_id: string, type: number, message?: string }[];

			this.messages.forEach(msg => {
				if (this.blocked.find(val => val == msg.user_id))
				{
					msg.message = '<message blocked>'
					msg.type = 1;
				}
			})
			this.generateRandomColors();
		});
	}

	fetchChannelHistory(channel: any) {
		this.http.get(`${GlobalConsts.userApi}/channels/history/` + channel.id, { headers: { password: this.password }, withCredentials: true }).subscribe(data => {

			this.messages = data as { id: string, user_id: string, type: number, username: string, message?: string }[];

			this.messages.forEach(msg => {
				if (this.blocked.find(val => val == msg.user_id))
				{
					msg.message = '<message blocked>'
					msg.type = 1;
				}
			})

			this.chat.id = channel.id;
			this.chat.name = channel.name;
			this.chat.public = true;

			this.generateRandomColors();
		});
	}

	fetchBlockedUsers() {
		this.http.get(`${GlobalConsts.userApi}/block/` + this.user.id, { withCredentials: true }).subscribe(data => {
			this.blocked = data as any[];
		});
	}

	ngOnInit(): void {
		this.subscription.add(this.data.isLoginData.subscribe(data => this.isLogin = data));

		this.fetchSub = setInterval(() => {
			
			if (this.isLogin)
			{
				
				this.fetchFriends();
				this.fetchChannels();
			}
			else
			{
				clearInterval(this.fetchSub);
			}

		}, 5000)
		if (this.isLogin) {
			this.socket = io(`ws://localhost:3001/${GlobalConsts.chatSockIo}`, {
				path: `/${GlobalConsts.chatSockIo}/socket.io`,
				withCredentials: true,
				transports: ['websocket']
			});

			this.socket.on('user', () => {
				this.http.get(`${GlobalConsts.userApi}/user/id`).subscribe((data: any) => {
					this.user = data;
					this.socket.emit('user', {user_id: data.id});
				})
			})

			this.socket.on('mod', (data: string) => {
				if (this.chat.id == data)
					this.chat.moderator = true;
				const chan = this.channelList.findIndex(val => val.id == data)
				if (chan >= 0)
					this.channelList[chan].moderator = true;
			});

			this.socket.on('unmod', (data: string) => {
				if (this.chat.id == data)
					this.chat.moderator = false;
				const chan = this.channelList.findIndex(val => val.id == data)
				if (chan >= 0)
					this.channelList[chan].moderator = false;
			})

			this.socket.on('mute', data => {
				this.dialog.open(DialogMuted, {
					data: {
						date: data.date
					}
				})
			})

			this.http.get(`${GlobalConsts.userApi}/user/id`, {withCredentials: true}).subscribe((data: any) => {
				this.user.id = data.id;
				this.fetchBlockedUsers();
			})

			this.socket.on('message', (data: {
				id: string,
				user_id: string,
				username: string,
				message: string,
				type: number
			}) => {

				data.user_id = String(data.user_id);

				if (this.blocked.find(val => val == data.user_id))
				{
					data.message = '<message blocked>'
					data.type = 1;
				}

				this.addMessage(data);
			})

			this.socket.on('ban', () => {
				if (this.chat.show && this.chat.public)
					this.openFriendList();
			});

			this.fetchChannels();
		}
	}

	ngOnDestroy(): void {

		if (this.socket.connected)
			this.socket.disconnect();

		clearInterval(this.fetchSub);
		this.subscription.unsubscribe();
	}

	addMessage(data: {
		id: string,
		user_id: string,
		message: string,
		type: number
		username?: string,
	}) {
		this.messages.push({ id: data.id, username: data.username, message: data.message, user_id: data.user_id, type: data.type });
		if (this.messages.length > MAX_MESSAGE)
			this.messages.splice(0, 1);
		this.generateRandomColors();
		this.scroll = true;
	}

	getStatusColor(friend: any) {
		if (friend.status == 1) //invite pending
			return '#e9d901';
		if (!friend.online)
			return '#700303';
		else if (friend.playing == true)
			return '#3843a7';
		else if (friend.online == 1)
			return '#3e7739';
		return '#e9d901';
	}

	addFriend(friend: any) {
		this.http.post(`${GlobalConsts.userApi}/friend/`, {
			first: this.user.id,
			second: friend.id
		}, { withCredentials: true }).subscribe({
			next:
				data => {
					this.fetchFriends();
				}
		})
	}

	generateRandomColors() {
		this.messages.forEach(val => {
			const tmp: string = val.user_id as string;
			if (!this.colorMap.has(tmp))
				this.colorMap.set(tmp, '#' + Math.floor(Math.random() * 16777215).toString(16));
		});
	}


	sendMessage() {
		let obj: {
			user_id: string,
			message: string,
			type: number,
			chat: { public: boolean, id: string },
			password?: string
		} = {
			user_id: this.user.id,
			message: this.input.nativeElement.value,
			type: 1,
			chat: { public: this.chat.public, id: this.chat.id },
		};

		if (this.chat.public)
			obj = { ...obj, password: this.password, message: this.input.nativeElement.value }
		else
			obj = { ...obj, password: this.password, message: this.inputPrivate.nativeElement.value }
		this.input.nativeElement.value = "";
		this.inputPrivate.nativeElement.value = "";
		this.socket.emit('message', obj);
	}

	openPrivate(friend: any) {
		this.socket.emit('connectRoom', { user_id: this.user.id, chat: { public: false, id: friend.id } });
		this.fetchPrivateMessage(friend);

		this.chat.id = friend.id;
		this.chat.name = friend.username;
		this.chat.public = false;
		if (!this.chat.show)
			this.chat.show = true;
		else
			this.chat.show = false;
	}

	connectRoom(channel: any) {
		this.http.get(`${GlobalConsts.userApi}/channels/access/` + channel.id,
			{ withCredentials: true })
			.subscribe({
				next: (data) => {
					
					if (data == 0) {
						
						this.socket.emit('connectRoom', { user_id: this.user.id, chat: { public: true, id: channel.id }, password: this.password });
						this.messages = [];
						this.chat = channel;
						this.chat.show = true;
						this.chat.public = true;
						this.scroll = true;
						
						this.fetchChannelHistory(channel);
					} else if (data == 2) //user is banned
					{
						alert('You were banned from this channel')
					} else if (data == 1) {
						alert('You have no access to this channel')
					}

				}
			});
	}

	openPublic(channel: any) {		
		if (channel.access == 1) //protected channel
		{			
			const tmp = this.dialog.open(DialogProtectedChat, {
				data: {
					id: channel.id
				}
			});

			tmp.afterClosed().subscribe(data => {				
				if (data && data.password)
					this.password = data.password;
				if (data && data.success) {
					this.connectRoom(channel);
					return;
				}
			});
		}
		else //open or private channel
		{
			if (!this.chat.show)
				this.connectRoom(channel);
			else
				this.chat.show = false;
		}
	}

	focusFriend(username: string) {
		this.focus = username;
	}

	unfocusFriend() {
		this.focus = "";
	}

	fetchFriends() {
		this.http.get(`${GlobalConsts.userApi}/friend/` + this.user.id, { withCredentials: true }).subscribe({
			next:
				data => {
					
					this.friendList = data as any[];
				},
			error:
				data => {
				}
		})
	}

	async openFriendList(event?: any) {
		
		this.socket.emit('disconnectRoom');
		this.chat.moderator = false;
		await this.sleep(100);
		this.fetchChannels();
		this.fetchFriends();
		this.chat.show = false;
		/*this.friendList.sort((a, b) => {
			return b.status - a.status;
		})
		*/

	}

	openUserDialog(message?: any) {
		if (message) {


			const tmp = this.dialog.open(DialogUser, {
				data: {
					username: message.username,
					id: message.user_id,
					my_id: this.user.id,
					friends: this.friendList,
					blocked: this.blocked
				}
			});
			tmp.afterClosed().subscribe(() => {
				this.fetchBlockedUsers();

			});
		}
		else {
			const tmp = this.dialog.open(DialogUser, {
				data: {
					username: this.chat.name,
					id: this.chat.id,
					my_id: this.user.id,
					friends: this.friendList,
					blocked: this.blocked
				}
			});

			tmp.afterClosed().subscribe(() => {
				this.fetchBlockedUsers();

			})
		}
	}

	openSpec() {
		this.http.get(`${GlobalConsts.userApi}/channels/${this.chat.id}`, {withCredentials: true}).subscribe(data => {
			if (data)
			{
				this.chat = {...this.chat, ...data};
				
				const tmp = this.dialog.open(DialogSpectator, {
					data:
					{
						chat: this.chat,
						my_id: this.user.id,
						friends: this.friendList,
						blocked: this.blocked,
						socket: this.socket
					}
				});
		
				tmp.afterClosed().subscribe(() => {
					this.fetchBlockedUsers();
				});
			}
			else
			{
				alert('Could not fetch channel details');
			}

		})

	}

	inviteFriend() {
		this.dialog.open(DialogInvite, {
			data: {
				chat: this.chat
			}
		})
	}

	inviteGame() {
			this.http.post(`${GlobalConsts.userApi}/game/custom`, {}).subscribe({
				next: (data: any) => {
					let obj = { type: 2, user_id: this.user.id, message: data.id, chat: this.chat };
					this.myGame = {id: data.id};
					this.socket.emit('message', obj);
					if (data.join)
						this.joinGame(this.myGame.id);
				},
				error: (err: any) => {
					
				},
			});
	}

	createChat() {
		const tmp = this.dialog.open(DialogCreateChat, {
			data: {
				user_id: this.user.id
			}
		});
		tmp.afterClosed().subscribe(data => {
			this.fetchChannels()
			if (data)
			{
				if (data.password)
					this.password = data.password;
				this.connectRoom({...data, moderator: true, creator: true});
			}
		})
	}

	joinGame(id: string | undefined, user?: string) {
		
		if (id != undefined) {			
			if (user == undefined || user != this.user.id)
			{
				this.join.emit(id)
				
			}
		}
		else
			this.join.emit(id)
	}
}
