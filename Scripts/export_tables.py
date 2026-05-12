import os
import pandas as pd
import json

# 配置文件夹路径
INPUT_DIR = "../Table/excel/"
OUTPUT_DIR = "../Table/json/"

def convert_excel_to_json():
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    if not os.path.exists(INPUT_DIR):
        os.makedirs(INPUT_DIR)
        print(f"请将 xlsx 文件放入 '{INPUT_DIR}' 文件夹。")
        return

    # 获取所有有效的 excel 文件
    excel_files = [f for f in os.listdir(INPUT_DIR) if f.endswith(".xlsx") and not f.startswith("~")]
    
    for filename in excel_files:
        file_path = os.path.join(INPUT_DIR, filename)
        print(f"正在读取文件: {filename}")
        
        try:
            # 使用 pd.ExcelFile 加载整个工作簿以获取所有 Sheet 名称
            xls = pd.ExcelFile(file_path)
            
            for sheet_name in xls.sheet_names:
                print(f"  -> 正在处理工作表: {sheet_name}")
                
                # 读取特定 Sheet
                df = pd.read_excel(xls, sheet_name=sheet_name)
                
                # 过滤掉全空的行和列
                df = df.dropna(how='all').dropna(axis=1, how='all')
                
                # 处理空值 (NaN -> None)
                df = df.where(pd.notnull(df), None)
                
                # 转换为字典列表
                json_data = df.to_dict(orient='records')
                
                # 命名规则：文件名_工作表名.json
                base_name = os.path.splitext(filename)[0]
                json_filename = f"{sheet_name}.json"
                json_path = os.path.join(OUTPUT_DIR, json_filename)
                
                with open(json_path, 'w', encoding='utf-8') as f:
                    json.dump(json_data, f, ensure_ascii=False, indent=4)
                    
                print(f"     [完成] 已导出: {json_filename}")
                
        except Exception as e:
            print(f"  [错误] 处理 {filename} 时发生异常: {e}")

if __name__ == "__main__":
    convert_excel_to_json()
    print("\n所有表格转换任务已结束！")