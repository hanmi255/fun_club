import os
import json
from mutagen import File

def format_duration(seconds):
    """将秒转换为“分钟:秒”格式的字符串"""
    minutes = seconds // 60
    seconds = seconds % 60
    return f"{minutes}:{seconds:02}"

def extract_audio_info(directory):
    """
    从指定目录中提取音频文件信息，包括标题、艺术家、播放时长、专辑、以及文件路径。
    """
    audio_files_info = []

    # 遍历指定目录下的所有文件
    for root, _, files in os.walk(directory):
        for file_name in files:
            # 构建文件的完整路径
            file_path = os.path.join(root, file_name)

            # 使用 mutagen 读取音频文件信息
            audio = File(file_path, easy=True)
            if audio:
                # 提取文件信息
                title = audio.get('title', [os.path.splitext(file_name)[0]])[0]  # 去除后缀名
                artist = audio.get('artist', ['Unknown Artist'])[0]
                # 从音频信息中获取时长（单位：秒），并格式化为分秒
                duration_seconds = int(audio.info.length) if audio.info else 0
                duration = format_duration(duration_seconds)
                album = audio.get('album', [title])[0]

                # 收集信息
                audio_files_info.append({
                    'title': title,
                    'artist': artist,
                    'duration': duration,
                    'album': album,
                    'file_path': file_path
                })

    return audio_files_info

def save_info_to_json(data, output_file):
    """
    将提取的信息保存到 JSON 文件中。
    """
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=4)

if __name__ == "__main__":
    # 指定要扫描的目录``
    directory = '../Resource/Music/'  # 请替换为你本地音频文件的目录路径
    # 指定输出的 JSON 文件名
    output_json_file = 'audio_files_info.json'

    # 提取音频文件信息
    audio_info = extract_audio_info(directory)
    # 保存信息到 JSON 文件
    save_info_to_json(audio_info, output_json_file)

    print(f"音频文件信息已保存到 {output_json_file}")
