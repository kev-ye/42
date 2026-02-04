import SwiftUI

struct MessagesListView: View {
    @EnvironmentObject var appState: AppState
    @State private var conversations: [(user: User, lastMessage: Message)] = []
    @State private var showingNewMessage = false
    @State private var currentUserId: Int64?
    
    var body: some View {
        NavigationView {
            List {
                ForEach(conversations, id: \.user.id) { conversation in
                    let contactName = DatabaseManager.shared.getContactName(forUserId: appState.currentUser?.id ?? 0, phoneNumber: conversation.user.phoneNumber)
                    NavigationLink(destination: ChatView(otherUser: conversation.user, otherUserName: contactName)) {
                        MessageRowView(user: conversation.user, lastMessage: conversation.lastMessage, currentUserId: appState.currentUser?.id ?? 0, contactName: contactName)
                    }
                }
            }
            .navigationTitle("messages".localized)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Rectangle()
                        .fill(appState.headerColor)
                        .frame(width: 50, height: 4)
                }
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button(action: { showingNewMessage = true }) {
                        Image(systemName: "square.and.pencil")
                    }
                }
            }
            .sheet(isPresented: $showingNewMessage) {
                NewMessageView(onSend: loadConversations)
            }
            .onAppear(perform: loadConversations)
            .onChange(of: appState.currentUser?.id) { _, newUserId in
                // 用户切换时重置状态
                currentUserId = newUserId
                loadConversations()
            }
        }
        .id(currentUserId) // 用户切换时重置NavigationView
    }
    
    private func loadConversations() {
        if let userId = appState.currentUser?.id {
            // 先检查并自动创建从消息中来的联系人
            DatabaseManager.shared.checkAndCreateContactsFromMessages(forUserId: userId)
            // 然后加载对话列表
            conversations = DatabaseManager.shared.getRecentConversations(forUserId: userId)
        }
    }
}

struct MessageRowView: View {
    let user: User
    let lastMessage: Message
    let currentUserId: Int64
    let contactName: String
    
    var body: some View {
        VStack(alignment: .leading, spacing: 4) {
            Text(contactName)
                .font(.headline)
            
            HStack {
                if lastMessage.senderId == currentUserId {
                    Text("you".localized + ": ")
                        .font(.subheadline)
                        .foregroundColor(.gray)
                }
                Text(lastMessage.content)
                    .font(.subheadline)
                    .foregroundColor(.gray)
                    .lineLimit(1)
                
                Spacer()
                
                Text(formatDate(lastMessage.timestamp))
                    .font(.caption)
                    .foregroundColor(.gray)
            }
        }
        .padding(.vertical, 4)
    }
    
    private func formatDate(_ date: Date) -> String {
        let calendar = Calendar.current
        if calendar.isDateInToday(date) {
            let formatter = DateFormatter()
            formatter.timeStyle = .short
            return formatter.string(from: date)
        } else if calendar.isDateInYesterday(date) {
            return "yesterday".localized
        } else {
            let formatter = DateFormatter()
            formatter.dateStyle = .short
            return formatter.string(from: date)
        }
    }
}
