import Foundation
import SQLite3

class DatabaseManager {
    static let shared = DatabaseManager()
    private var db: OpaquePointer?
    
    private init() {
        openDatabase()
        createTables()
    }
    
    private func openDatabase() {
        let fileURL = try! FileManager.default
            .url(for: .documentDirectory, in: .userDomainMask, appropriateFor: nil, create: false)
            .appendingPathComponent("ft_hangouts.sqlite")
        
        if sqlite3_open(fileURL.path, &db) != SQLITE_OK {
            print("Error opening database")
        }
    }
    
    private func createTables() {
        let createUserTable = """
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            phone_number TEXT UNIQUE NOT NULL,
            created_at REAL NOT NULL
        );
        """
        
        let createContactTable = """
        CREATE TABLE IF NOT EXISTS contacts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            phone_number TEXT NOT NULL,
            email TEXT,
            address TEXT,
            birthday TEXT,
            notes TEXT,
            photo_data BLOB,
            created_at REAL NOT NULL,
            FOREIGN KEY (user_id) REFERENCES users (id)
        );
        """
        
        let createMessageTable = """
        CREATE TABLE IF NOT EXISTS messages (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            sender_id INTEGER NOT NULL,
            receiver_id INTEGER NOT NULL,
            content TEXT NOT NULL,
            timestamp REAL NOT NULL,
            is_read INTEGER DEFAULT 0,
            FOREIGN KEY (sender_id) REFERENCES users (id),
            FOREIGN KEY (receiver_id) REFERENCES users (id)
        );
        """
        
        let createDeletedContactsTable = """
        CREATE TABLE IF NOT EXISTS deleted_contacts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            phone_number TEXT NOT NULL,
            deleted_at REAL NOT NULL,
            UNIQUE(user_id, phone_number)
        );
        """
        
        executeSQL(createUserTable)
        executeSQL(createContactTable)
        executeSQL(createMessageTable)
        executeSQL(createDeletedContactsTable)
    }
    
    private func executeSQL(_ sql: String) {
        var statement: OpaquePointer?
        if sqlite3_prepare_v2(db, sql, -1, &statement, nil) == SQLITE_OK {
            if sqlite3_step(statement) == SQLITE_DONE {
                print("Table created successfully")
            }
        }
        sqlite3_finalize(statement)
    }
    
    // MARK: - User Operations
    
    func getOrCreateUser(phoneNumber: String) -> User {
        if let user = getUser(phoneNumber: phoneNumber) {
            return user
        }
        return createUser(phoneNumber: phoneNumber)
    }
    
    func getUser(phoneNumber: String) -> User? {
        let query = "SELECT id, phone_number, created_at FROM users WHERE phone_number = ?;"
        var statement: OpaquePointer?
        var user: User?
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_text(statement, 1, (phoneNumber as NSString).utf8String, -1, nil)
            
            if sqlite3_step(statement) == SQLITE_ROW {
                let id = sqlite3_column_int64(statement, 0)
                let phone = String(cString: sqlite3_column_text(statement, 1))
                let createdAt = Date(timeIntervalSince1970: sqlite3_column_double(statement, 2))
                user = User(id: id, phoneNumber: phone, createdAt: createdAt)
            }
        }
        sqlite3_finalize(statement)
        return user
    }
    
    private func createUser(phoneNumber: String) -> User {
        let insert = "INSERT INTO users (phone_number, created_at) VALUES (?, ?);"
        var statement: OpaquePointer?
        let now = Date()
        
        if sqlite3_prepare_v2(db, insert, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_text(statement, 1, (phoneNumber as NSString).utf8String, -1, nil)
            sqlite3_bind_double(statement, 2, now.timeIntervalSince1970)
            
            if sqlite3_step(statement) == SQLITE_DONE {
                let id = sqlite3_last_insert_rowid(db)
                sqlite3_finalize(statement)
                return User(id: id, phoneNumber: phoneNumber, createdAt: now)
            }
        }
        sqlite3_finalize(statement)
        return User(id: nil, phoneNumber: phoneNumber, createdAt: now)
    }
    
    func getAllUsers() -> [User] {
        let query = "SELECT id, phone_number, created_at FROM users;"
        var statement: OpaquePointer?
        var users: [User] = []
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            while sqlite3_step(statement) == SQLITE_ROW {
                let id = sqlite3_column_int64(statement, 0)
                let phone = String(cString: sqlite3_column_text(statement, 1))
                let createdAt = Date(timeIntervalSince1970: sqlite3_column_double(statement, 2))
                users.append(User(id: id, phoneNumber: phone, createdAt: createdAt))
            }
        }
        sqlite3_finalize(statement)
        return users
    }
    
    // MARK: - Contact Operations
    
    func createContact(_ contact: Contact) -> Contact {
        let insert = """
        INSERT INTO contacts (user_id, name, phone_number, email, address, birthday, notes, photo_data, created_at)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);
        """
        var statement: OpaquePointer?
        
        if sqlite3_prepare_v2(db, insert, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, contact.userId)
            sqlite3_bind_text(statement, 2, (contact.name as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 3, (contact.phoneNumber as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 4, (contact.email as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 5, (contact.address as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 6, (contact.birthday as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 7, (contact.notes as NSString).utf8String, -1, nil)
            
            if let photoData = contact.photoData {
                sqlite3_bind_blob(statement, 8, (photoData as NSData).bytes, Int32(photoData.count), nil)
            } else {
                sqlite3_bind_null(statement, 8)
            }
            
            sqlite3_bind_double(statement, 9, contact.createdAt.timeIntervalSince1970)
            
            if sqlite3_step(statement) == SQLITE_DONE {
                let id = sqlite3_last_insert_rowid(db)
                sqlite3_finalize(statement)
                var newContact = contact
                newContact.id = id
                return newContact
            }
        }
        sqlite3_finalize(statement)
        return contact
    }
    
    func getContacts(forUserId userId: Int64) -> [Contact] {
        let query = "SELECT * FROM contacts WHERE user_id = ? ORDER BY name;"
        var statement: OpaquePointer?
        var contacts: [Contact] = []
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, userId)
            
            while sqlite3_step(statement) == SQLITE_ROW {
                let id = sqlite3_column_int64(statement, 0)
                let userId = sqlite3_column_int64(statement, 1)
                let name = String(cString: sqlite3_column_text(statement, 2))
                let phone = String(cString: sqlite3_column_text(statement, 3))
                let email = sqlite3_column_text(statement, 4) != nil ? String(cString: sqlite3_column_text(statement, 4)) : ""
                let address = sqlite3_column_text(statement, 5) != nil ? String(cString: sqlite3_column_text(statement, 5)) : ""
                let birthday = sqlite3_column_text(statement, 6) != nil ? String(cString: sqlite3_column_text(statement, 6)) : ""
                let notes = sqlite3_column_text(statement, 7) != nil ? String(cString: sqlite3_column_text(statement, 7)) : ""
                
                var photoData: Data?
                if let blob = sqlite3_column_blob(statement, 8) {
                    let size = sqlite3_column_bytes(statement, 8)
                    photoData = Data(bytes: blob, count: Int(size))
                }
                
                let createdAt = Date(timeIntervalSince1970: sqlite3_column_double(statement, 9))
                
                contacts.append(Contact(id: id, userId: userId, name: name, phoneNumber: phone,
                                      email: email, address: address, birthday: birthday,
                                      notes: notes, photoData: photoData, createdAt: createdAt))
            }
        }
        sqlite3_finalize(statement)
        return contacts
    }
    
    func updateContact(_ contact: Contact) {
        let update = """
        UPDATE contacts SET name = ?, phone_number = ?, email = ?, address = ?,
        birthday = ?, notes = ?, photo_data = ? WHERE id = ?;
        """
        var statement: OpaquePointer?
        
        if sqlite3_prepare_v2(db, update, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_text(statement, 1, (contact.name as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 2, (contact.phoneNumber as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 3, (contact.email as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 4, (contact.address as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 5, (contact.birthday as NSString).utf8String, -1, nil)
            sqlite3_bind_text(statement, 6, (contact.notes as NSString).utf8String, -1, nil)
            
            if let photoData = contact.photoData {
                sqlite3_bind_blob(statement, 7, (photoData as NSData).bytes, Int32(photoData.count), nil)
            } else {
                sqlite3_bind_null(statement, 7)
            }
            
            sqlite3_bind_int64(statement, 8, contact.id!)
            sqlite3_step(statement)
        }
        sqlite3_finalize(statement)
    }
    
    func deleteContact(_ contact: Contact) {
        // 删除联系人
        let delete = "DELETE FROM contacts WHERE id = ?;"
        var statement: OpaquePointer?
        
        if sqlite3_prepare_v2(db, delete, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, contact.id!)
            sqlite3_step(statement)
        }
        sqlite3_finalize(statement)
        
        // 记录到已删除表，避免自动重建
        let insert = "INSERT OR REPLACE INTO deleted_contacts (user_id, phone_number, deleted_at) VALUES (?, ?, ?);"
        var insertStatement: OpaquePointer?
        
        if sqlite3_prepare_v2(db, insert, -1, &insertStatement, nil) == SQLITE_OK {
            sqlite3_bind_int64(insertStatement, 1, contact.userId)
            sqlite3_bind_text(insertStatement, 2, (contact.phoneNumber as NSString).utf8String, -1, nil)
            sqlite3_bind_double(insertStatement, 3, Date().timeIntervalSince1970)
            sqlite3_step(insertStatement)
        }
        sqlite3_finalize(insertStatement)
    }
    
    // MARK: - Message Operations
    
    func sendMessage(from senderId: Int64, to receiverId: Int64, content: String) -> Message? {
        let insert = "INSERT INTO messages (sender_id, receiver_id, content, timestamp, is_read) VALUES (?, ?, ?, ?, 0);"
        var statement: OpaquePointer?
        let now = Date()
        
        if sqlite3_prepare_v2(db, insert, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, senderId)
            sqlite3_bind_int64(statement, 2, receiverId)
            sqlite3_bind_text(statement, 3, (content as NSString).utf8String, -1, nil)
            sqlite3_bind_double(statement, 4, now.timeIntervalSince1970)
            
            if sqlite3_step(statement) == SQLITE_DONE {
                let id = sqlite3_last_insert_rowid(db)
                sqlite3_finalize(statement)
                return Message(id: id, senderId: senderId, receiverId: receiverId,
                             content: content, timestamp: now, isRead: false)
            }
        }
        sqlite3_finalize(statement)
        return nil
    }
    
    func getMessages(between user1: Int64, and user2: Int64) -> [Message] {
        let query = """
        SELECT * FROM messages
        WHERE (sender_id = ? AND receiver_id = ?) OR (sender_id = ? AND receiver_id = ?)
        ORDER BY timestamp;
        """
        var statement: OpaquePointer?
        var messages: [Message] = []
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, user1)
            sqlite3_bind_int64(statement, 2, user2)
            sqlite3_bind_int64(statement, 3, user2)
            sqlite3_bind_int64(statement, 4, user1)
            
            while sqlite3_step(statement) == SQLITE_ROW {
                let id = sqlite3_column_int64(statement, 0)
                let senderId = sqlite3_column_int64(statement, 1)
                let receiverId = sqlite3_column_int64(statement, 2)
                let content = String(cString: sqlite3_column_text(statement, 3))
                let timestamp = Date(timeIntervalSince1970: sqlite3_column_double(statement, 4))
                let isRead = sqlite3_column_int(statement, 5) == 1
                
                messages.append(Message(id: id, senderId: senderId, receiverId: receiverId,
                                      content: content, timestamp: timestamp, isRead: isRead))
            }
        }
        sqlite3_finalize(statement)
        return messages
    }
    
    // MARK: - Auto-create contacts from received messages
    
    func checkAndCreateContactsFromMessages(forUserId userId: Int64) {
        // 查找所有收到的消息的发送者
        let query = """
        SELECT DISTINCT sender_id
        FROM messages
        WHERE receiver_id = ?;
        """
        var statement: OpaquePointer?
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, userId)
            
            let existingContacts = getContacts(forUserId: userId)
            
            while sqlite3_step(statement) == SQLITE_ROW {
                let senderId = sqlite3_column_int64(statement, 0)
                if let user = getUserById(senderId) {
                    // 检查是否已经有这个联系人
                    let contactExists = existingContacts.contains { $0.phoneNumber == user.phoneNumber }
                    
                    // 检查是否被用户主动删除过
                    let wasDeleted = isContactDeleted(userId: userId, phoneNumber: user.phoneNumber)
                    
                    if !contactExists && !wasDeleted {
                        // 自动创建联系人
                        let newContact = Contact(
                            userId: userId,
                            name: user.phoneNumber,
                            phoneNumber: user.phoneNumber,
                            email: "",
                            address: "",
                            birthday: "",
                            notes: "",
                            photoData: nil,
                            createdAt: Date()
                        )
                        _ = createContact(newContact)
                    }
                }
            }
        }
        sqlite3_finalize(statement)
    }
    
    func getRecentConversations(forUserId userId: Int64) -> [(user: User, lastMessage: Message)] {
        let query = """
        SELECT DISTINCT
            CASE WHEN sender_id = ? THEN receiver_id ELSE sender_id END as other_user_id
        FROM messages
        WHERE sender_id = ? OR receiver_id = ?;
        """
        var statement: OpaquePointer?
        var conversations: [(user: User, lastMessage: Message)] = []
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, userId)
            sqlite3_bind_int64(statement, 2, userId)
            sqlite3_bind_int64(statement, 3, userId)
            
            while sqlite3_step(statement) == SQLITE_ROW {
                let otherUserId = sqlite3_column_int64(statement, 0)
                if let user = getUserById(otherUserId) {
                    let messages = getMessages(between: userId, and: otherUserId)
                    if let lastMessage = messages.last {
                        conversations.append((user: user, lastMessage: lastMessage))
                    }
                }
            }
        }
        sqlite3_finalize(statement)
        
        return conversations.sorted { $0.lastMessage.timestamp > $1.lastMessage.timestamp }
    }
    
    func getContactName(forUserId userId: Int64, phoneNumber: String) -> String {
        let query = "SELECT name FROM contacts WHERE user_id = ? AND phone_number = ?;"
        var statement: OpaquePointer?
        var name: String?
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, userId)
            sqlite3_bind_text(statement, 2, (phoneNumber as NSString).utf8String, -1, nil)
            
            if sqlite3_step(statement) == SQLITE_ROW {
                name = String(cString: sqlite3_column_text(statement, 0))
            }
        }
        sqlite3_finalize(statement)
        
        return name ?? phoneNumber
    }
    
    private func getUserById(_ id: Int64) -> User? {
        let query = "SELECT id, phone_number, created_at FROM users WHERE id = ?;"
        var statement: OpaquePointer?
        var user: User?
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, id)
            
            if sqlite3_step(statement) == SQLITE_ROW {
                let id = sqlite3_column_int64(statement, 0)
                let phone = String(cString: sqlite3_column_text(statement, 1))
                let createdAt = Date(timeIntervalSince1970: sqlite3_column_double(statement, 2))
                user = User(id: id, phoneNumber: phone, createdAt: createdAt)
            }
        }
        sqlite3_finalize(statement)
        return user
    }
    
    private func isContactDeleted(userId: Int64, phoneNumber: String) -> Bool {
        let query = "SELECT id FROM deleted_contacts WHERE user_id = ? AND phone_number = ?;"
        var statement: OpaquePointer?
        var exists = false
        
        if sqlite3_prepare_v2(db, query, -1, &statement, nil) == SQLITE_OK {
            sqlite3_bind_int64(statement, 1, userId)
            sqlite3_bind_text(statement, 2, (phoneNumber as NSString).utf8String, -1, nil)
            
            if sqlite3_step(statement) == SQLITE_ROW {
                exists = true
            }
        }
        sqlite3_finalize(statement)
        
        return exists
    }
}
