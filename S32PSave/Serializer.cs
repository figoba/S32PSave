using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace S32PSave
{
    class Serializer
    {
        /// <summary>
        /// 序列化类到xml文档
        /// </summary>
        /// <typeparam name="T">类</typeparam>
        /// <param name="obj">类的对象</param>
        /// <param name="filePath">xml文档路径（包含文件名）</param>
        /// <returns>成功：true，失败：false</returns>
        public static bool CreateXML<T>(T obj, string filePath)
        {
            XmlWriter writer = null;    //声明一个xml编写器
            XmlWriterSettings writerSetting = new XmlWriterSettings //声明编写器设置
            {
                Indent = true,//定义xml格式，自动创建新的行
                Encoding = UTF8Encoding.UTF8,//编码格式
            };

            try
            {
                //创建一个保存数据到xml文档的流
                writer = XmlWriter.Create(filePath, writerSetting);
            }
            catch (Exception ex)
            {
                //_logServ.Error(string.Format("创建xml文档失败：{0}", ex.Message));
                return false;
            }

            XmlSerializer xser = new XmlSerializer(typeof(T));  //实例化序列化对象

            try
            {
                xser.Serialize(writer, obj);  //序列化对象到xml文档
            }
            catch (Exception ex)
            {
                //_logServ.Error(string.Format("创建xml文档失败：{0}", ex.Message));
                return false;
            }
            finally
            {
                writer.Close();
            }
            return true;
        }

        /// <summary>
        /// 从 XML 文档中反序列化为对象
        /// </summary>
        /// <param name="filePath">文档路径（包含文档名）</param>
        /// <param name="type">对象的类型</param>
        /// <returns>返回object类型</returns>
        public static object FromXmlString(string filePath, Type type)
        {
            if (!File.Exists(filePath)) {
                return null;
            }
            string xmlString = File.ReadAllText(filePath);

            if (string.IsNullOrEmpty(xmlString))
            {
                return null;
            }
            using (MemoryStream stream = new MemoryStream(Encoding.UTF8.GetBytes(xmlString)))
            {
                XmlSerializer serializer = new XmlSerializer(type);
                try
                {
                    return serializer.Deserialize(stream);
                }
                catch
                {
                    return null;
                }
            }

        }
    }
}
