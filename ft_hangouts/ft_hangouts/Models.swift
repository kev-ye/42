import Foundation

struct User: Identifiable, Codable {
    var id: Int64?
    var phoneNumber: String
    var createdAt: Date
}

struct Contact: Identifiable, Codable {
    var id: Int64?
    var userId: Int64
    var name: String
    var phoneNumber: String
    var email: String
    var address: String
    var birthday: String
    var notes: String
    var photoData: Data?
    var createdAt: Date
}

struct Message: Identifiable, Codable {
    var id: Int64?
    var senderId: Int64
    var receiverId: Int64
    var content: String
    var timestamp: Date
    var isRead: Bool
}
