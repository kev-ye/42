import SwiftUI

struct NewMessageView: View {
    @EnvironmentObject var appState: AppState
    @Environment(\.dismiss) var dismiss
    
    @State private var phoneNumber = ""
    @State private var messageContent = ""
    @State private var showError = false
    @State private var errorMessage = ""
    
    let onSend: () -> Void
    
    var body: some View {
        NavigationView {
            Form {
                Section(header: Text("recipient".localized)) {
                    TextField("phone_number".localized, text: $phoneNumber)
                        .keyboardType(.phonePad)
                }
                
                Section(header: Text("message".localized)) {
                    TextEditor(text: $messageContent)
                        .frame(minHeight: 100)
                }
                
                if showError {
                    Section {
                        Text(errorMessage)
                            .foregroundColor(.red)
                    }
                }
            }
            .navigationTitle("new_message".localized)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Button("cancel".localized) {
                        dismiss()
                    }
                }
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button("send".localized) {
                        sendMessage()
                    }
                    .disabled(phoneNumber.isEmpty || messageContent.isEmpty)
                }
            }
        }
    }
    
    private func sendMessage() {
        guard let currentUser = appState.currentUser, let senderId = currentUser.id else { return }
        
        // Check if receiver exists (do NOT create automatically)
        guard let receiverUser = DatabaseManager.shared.getUser(phoneNumber: phoneNumber),
              let receiverId = receiverUser.id else {
            errorMessage = "user_not_found".localized
            showError = true
            return
        }
        
        if let _ = DatabaseManager.shared.sendMessage(from: senderId, to: receiverId, content: messageContent) {
            onSend()
            dismiss()
        } else {
            errorMessage = "send_failed".localized
            showError = true
        }
    }
}
