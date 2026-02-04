import 'package:flutter/material.dart';

// User detail view
class UserDetailView extends StatelessWidget {
  final Map<String, dynamic> userData;

  const UserDetailView({super.key, required this.userData});

  // Helper method to safely format level value
  String _formatLevel(dynamic level) {
    if (level == null) return 'N/A';
    final levelDouble = (level is num) ? level.toDouble() : (level is String ? double.tryParse(level) : null);
    if (levelDouble == null || levelDouble.isNaN || levelDouble.isInfinite) return 'N/A';
    return levelDouble.toStringAsFixed(2);
  }

  @override
  Widget build(BuildContext context) {
    final cursusUsers = userData['cursus_users'] as List? ?? [];
    final mainCursus = cursusUsers.isNotEmpty ? cursusUsers.last : null;
    final skills = mainCursus?['skills'] as List? ?? [];
    final projectsUsers = userData['projects_users'] as List? ?? [];

    return Scaffold(
      appBar: AppBar(
        title: Text(userData['login'] ?? 'User Details'),
      ),
      body: SingleChildScrollView(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Center(
              child: CircleAvatar(
                radius: 60,
                backgroundImage: userData['image']?['versions']?['large'] != null
                    ? NetworkImage(userData['image']['versions']['large'] as String)
                    : null,
                child: userData['image']?['versions']?['large'] == null
                    ? const Icon(Icons.person, size: 60)
                    : null,
              ),
            ),
            const SizedBox(height: 24),
            _buildInfoCard('Basic Information', [
              _buildInfoRow('Login', userData['login']?.toString()),
              _buildInfoRow('Email', userData['email']?.toString()),
              _buildInfoRow('Mobile', userData['phone']?.toString()),
              _buildInfoRow('Wallet', '${userData['wallet'] ?? 0} ₳'),
              _buildInfoRow('Level', _formatLevel(mainCursus?['level'])),
              _buildInfoRow('Location', userData['location']?.toString() ?? 'Unavailable'),
              _buildInfoRow('Evaluation Points', '${userData['correction_point'] ?? 0}'),
            ]),
            const SizedBox(height: 16),
            if (skills.isNotEmpty) ...[
              const Text(
                'Skills',
                style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
              ),
              const SizedBox(height: 8),
              Card(
                child: Padding(
                  padding: const EdgeInsets.all(12),
                  child: Column(
                    children: skills.map<Widget>((skill) {
                      // Safely convert level to double, handling null, NaN, and invalid types
                      final levelValue = skill['level'];
                      double level = 0.0;
                      if (levelValue != null) {
                        if (levelValue is num) {
                          level = levelValue.toDouble();
                        } else if (levelValue is String) {
                          level = double.tryParse(levelValue) ?? 0.0;
                        }
                      }
                      // Ensure level is a valid number (not NaN or Infinity)
                      if (level.isNaN || level.isInfinite) {
                        level = 0.0;
                      }
                      
                      // Calculate percentage safely
                      final percentage = (level % 1) * 100;
                      // Clamp percentage to valid range and ensure it's not NaN
                      final safePercentage = percentage.isNaN || percentage.isInfinite 
                          ? 0.0 
                          : percentage.clamp(0.0, 100.0);
                      
                      // Clamp progress value to valid range for LinearProgressIndicator
                      final progressValue = (safePercentage / 100).clamp(0.0, 1.0);
                      
                      return Padding(
                        padding: const EdgeInsets.symmetric(vertical: 8),
                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            Row(
                              mainAxisAlignment: MainAxisAlignment.spaceBetween,
                              children: [
                                Expanded(
                                  child: Text(
                                    skill['name']?.toString() ?? '',
                                    overflow: TextOverflow.ellipsis,
                                  ),
                                ),
                                const SizedBox(width: 8),
                                Text(
                                  'Lv ${level.toStringAsFixed(2)} (${safePercentage.toStringAsFixed(0)}%)',
                                  style: const TextStyle(fontWeight: FontWeight.w500),
                                ),
                              ],
                            ),
                            const SizedBox(height: 4),
                            LinearProgressIndicator(
                              value: progressValue,
                              backgroundColor: Colors.grey[300],
                            ),
                          ],
                        ),
                      );
                    }).toList(),
                  ),
                ),
              ),
              const SizedBox(height: 16),
            ],
            // Filter and display only completed projects (including failed ones)
            if (projectsUsers.isNotEmpty) ...[
              Builder(
                builder: (context) {
                  print('project users: $projectsUsers');
                  // Filter to show only finished projects (completed, including failed)
                  final completedProjects = projectsUsers.where((project) {
                    final status = project['status']?.toString() ?? '';
                    return status == 'finished';
                  }).toList();

                  if (completedProjects.isEmpty) {
                    return const SizedBox.shrink();
                  }

                  return Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      const Text(
                        'Completed Projects',
                        style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
                      ),
                      const SizedBox(height: 8),
                      Card(
                        child: Padding(
                          padding: const EdgeInsets.all(12),
                          child: Column(
                            children: completedProjects.map<Widget>((project) {
                              final validated = project['validated?'] as bool?;
                              final finalMark = project['final_mark'] as int?;
                              final projectName = project['project']?['name']?.toString() ?? 'Unknown';

                              // Completed projects can only be Passed or Failed
                              final isPassed = validated == true;
                              final statusColor = isPassed ? Colors.green : Colors.red;
                              final statusIcon = isPassed ? Icons.check_circle : Icons.cancel;
                              final statusText = isPassed ? 'Passed' : 'Failed';

                              return ListTile(
                                leading: Icon(
                                  statusIcon,
                                  color: statusColor,
                                ),
                                title: Text(projectName),
                                subtitle: Text(statusText),
                                trailing: finalMark != null
                                    ? Text(
                                        '$finalMark/100',
                                        style: TextStyle(
                                          color: statusColor,
                                          fontWeight: FontWeight.bold,
                                        ),
                                      )
                                    : null,
                              );
                            }).toList(),
                          ),
                        ),
                      ),
                    ],
                  );
                },
              ),
            ],
          ],
        ),
      ),
    );
  }

  Widget _buildInfoCard(String title, List<Widget> children) {
    return Card(
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(
              title,
              style: const TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
            ),
            const SizedBox(height: 12),
            ...children,
          ],
        ),
      ),
    );
  }

  Widget _buildInfoRow(String label, String? value) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 4),
      child: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          SizedBox(
            width: 140,
            child: Text(
              '$label:',
              style: const TextStyle(fontWeight: FontWeight.w500),
            ),
          ),
          const SizedBox(width: 8),
          Expanded(
            child: Text(
              value ?? 'N/A',
              overflow: TextOverflow.ellipsis,
              maxLines: 2,
            ),
          ),
        ],
      ),
    );
  }
}

