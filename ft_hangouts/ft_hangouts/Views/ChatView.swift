import SwiftUI

struct ChatView: View {
    @EnvironmentObject var appState: AppState
    @State private var messages: [Message] = []
    @State private var newMessage = ""
    @State private var showError = false
    @State private var errorMessage = ""
    
    let otherUser: User
    let otherUserName: String
    
    var body: some View {
        VStack {
            ScrollViewReader { proxy in
                ScrollView {
                    LazyVStack(spacing: 8) {
                        ForEach(messages) { message in
                            MessageBubble(
                                message: message,
                                isFromCurrentUser: message.senderId == appState.currentUser?.id
                            )
                            .id(message.id)
                        }
                    }
                    .padding()
                }
                .onChange(of: messages.count) { _, _ in
                    if let lastMessage = messages.last {
                        withAnimation {
                            proxy.scrollTo(lastMessage.id, anchor: .bottom)
                        }
                    }
                }
            }
            
            if showError {
                Text(errorMessage)
                    .foregroundColor(.red)
                    .font(.caption)
                    .padding(.horizontal)
            }
            
            HStack {
                TextField("type_message".localized, text: $newMessage)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding(.leading)
                
                Button(action: sendMessage) {
                    Image(systemName: "arrow.up.circle.fill")
                        .font(.system(size: 32))
                        .foregroundColor(.blue)
                }
                .padding(.trailing)
                .disabled(newMessage.isEmpty)
            }
            .padding(.vertical, 8)
        }
        .navigationTitle(otherUserName)
        .navigationBarTitleDisplayMode(.inline)
        .onAppear(perform: loadMessages)
    }
    
    private func loadMessages() {
        guard let currentUserId = appState.currentUser?.id,
              let otherUserId = otherUser.id else { return }
        
        messages = DatabaseManager.shared.getMessages(between: currentUserId, and: otherUserId)
    }
    
    private func sendMessage() {
        guard let currentUserId = appState.currentUser?.id,
              let otherUserId = otherUser.id else { return }
        
        guard !newMessage.isEmpty else { return }
        
        if let message = DatabaseManager.shared.sendMessage(from: currentUserId, to: otherUserId, content: newMessage) {
            messages.append(message)
            newMessage = ""
            showError = false
        } else {
            errorMessage = "send_failed".localized
            showError = true
            DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
                showError = false
            }
        }
    }
}

struct MessageBubble: View {
    let message: Message
    let isFromCurrentUser: Bool
    
    var body: some View {
        HStack {
            if isFromCurrentUser {
                Spacer()
            }
            
            VStack(alignment: isFromCurrentUser ? .trailing : .leading, spacing: 4) {
                Text(message.content)
                    .padding(12)
                    .background(isFromCurrentUser ? Color.blue : Color.gray.opacity(0.2))
                    .foregroundColor(isFromCurrentUser ? .white : .primary)
                    .cornerRadius(16)
                
                Text(formatTime(message.timestamp))
                    .font(.caption2)
                    .foregroundColor(.gray)
            }
            .frame(maxWidth: 250, alignment: isFromCurrentUser ? .trailing : .leading)
            
            if !isFromCurrentUser {
                Spacer()
            }
        }
    }
    
    private func formatTime(_ date: Date) -> String {
        let formatter = DateFormatter()
        formatter.timeStyle = .short
        return formatter.string(from: date)
    }
}
